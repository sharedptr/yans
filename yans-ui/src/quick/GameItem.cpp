#include "GameItem.h"

#include "render/detail/RenderThread.h"
#include "render/detail/TextureNode.h"

#include <QtCore/QMutex>
#include <QtCore/QThread>

#include <QtGui/QGuiApplication>
#include <QtGui/QOffscreenSurface>
#include <QtGui/QOpenGLContext>
#include <QtGui/QOpenGLFramebufferObject>

#include <QtQuick/QQuickWindow>
#include <qsgsimpletexturenode.h>

YANS_UNS_B1( quick )

GameItem::GameItem() : m_renderThread( new render::detail::RenderThread( QSize( 1024, 1024 ) ) )
{
    setFlag( ItemHasContents, true );
}

GameItem::~GameItem()
{
    emit shutdown();
    m_renderThread->wait();
    delete m_renderThread;
}

void GameItem::ready()
{
    m_renderThread->surface = new QOffscreenSurface();
    m_renderThread->surface->setFormat( m_renderThread->context->format() );
    m_renderThread->surface->create();

    m_renderThread->moveToThread( m_renderThread );

    connect( window(), &QQuickWindow::sceneGraphInvalidated, m_renderThread, &render::detail::RenderThread::shutDown,
             Qt::QueuedConnection );
    connect( this, &GameItem::shutdown, m_renderThread, &render::detail::RenderThread::shutDown, Qt::QueuedConnection );

    m_renderThread->start();
    update();
}

QSGNode* GameItem::updatePaintNode( QSGNode* oldNode, UpdatePaintNodeData* )
{
    render::detail::TextureNode* node = static_cast< render::detail::TextureNode* >( oldNode );

    if( !m_renderThread->context )
    {
        QOpenGLContext* current = window()->openglContext();
        // Some GL implementations requres that the currently bound context is
        // made non-current before we set up sharing, so we doneCurrent here
        // and makeCurrent down below while setting up our own context.
        current->doneCurrent();

        m_renderThread->context = new QOpenGLContext();
        m_renderThread->context->setFormat( current->format() );
        m_renderThread->context->setShareContext( current );
        m_renderThread->context->create();
        m_renderThread->context->moveToThread( m_renderThread );

        current->makeCurrent( window() );

        QMetaObject::invokeMethod( this, "ready" );
        return 0;
    }

    if( !node )
    {
        node = new render::detail::TextureNode( window() );

        /* Set up connections to get the production of FBO textures in sync with vsync on the
         * rendering thread.
         *
         * When a new texture is ready on the rendering thread, we use a direct connection to
         * the texture node to let it know a new texture can be used. The node will then
         * emit pendingNewTexture which we bind to QQuickWindow::update to schedule a redraw.
         *
         * When the scene graph starts rendering the next frame, the prepareNode() function
         * is used to update the node with the new texture. Once it completes, it emits
         * textureInUse() which we connect to the FBO rendering thread's renderNext() to have
         * it start producing content into its current "back buffer".
         *
         * This FBO rendering pipeline is throttled by vsync on the scene graph rendering thread.
         */
        connect( m_renderThread, &render::detail::RenderThread::textureReady, node,
                 &render::detail::TextureNode::newTexture, Qt::DirectConnection );
        connect( node, &render::detail::TextureNode::pendingNewTexture, window(), &QQuickWindow::update,
                 Qt::QueuedConnection );
        connect( window(), &QQuickWindow::beforeRendering, node, &render::detail::TextureNode::prepareNode,
                 Qt::DirectConnection );
        connect( node, &render::detail::TextureNode::textureInUse, m_renderThread,
                 &render::detail::RenderThread::renderNext, Qt::QueuedConnection );

        // Get the production of FBO textures started..
        QMetaObject::invokeMethod( m_renderThread, "renderNext", Qt::QueuedConnection );
    }

    node->setRect( boundingRect() );

    return node;
}

YANS_UNS_E1( quick )
