#include "ThreadRenderer.h"

#include "render/private/RenderThread.h"
#include "render/private/TextureNode.h"

#include <QtCore/QMutex>
#include <QtCore/QThread>

#include <QtGui/QGuiApplication>
#include <QtGui/QOffscreenSurface>
#include <QtGui/QOpenGLContext>
#include <QtGui/QOpenGLFramebufferObject>

#include <QtQuick/QQuickWindow>
#include <qsgsimpletexturenode.h>

QList< QThread * > ThreadRenderer::threads;

ThreadRenderer::ThreadRenderer() : m_renderThread( nullptr )
{
    setFlag( ItemHasContents, true );
    m_renderThread = new RenderThread( QSize( 1024, 1024 ) );
}

void ThreadRenderer::ready()
{
    m_renderThread->surface = new QOffscreenSurface();
    m_renderThread->surface->setFormat( m_renderThread->context->format() );
    m_renderThread->surface->create();

    m_renderThread->moveToThread( m_renderThread );

    connect( window(), &QQuickWindow::sceneGraphInvalidated, m_renderThread, &RenderThread::shutDown,
             Qt::QueuedConnection );

    m_renderThread->start();
    update();
}

QSGNode *ThreadRenderer::updatePaintNode( QSGNode *oldNode, UpdatePaintNodeData * )
{
    TextureNode *node = static_cast< TextureNode * >( oldNode );

    if( !m_renderThread->context )
    {
        QOpenGLContext *current = window()->openglContext();
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
        node = new TextureNode( window() );

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
        connect( m_renderThread, &RenderThread::textureReady, node, &TextureNode::newTexture, Qt::DirectConnection );
        connect( node, &TextureNode::pendingNewTexture, window(), &QQuickWindow::update, Qt::QueuedConnection );
        connect( window(), &QQuickWindow::beforeRendering, node, &TextureNode::prepareNode, Qt::DirectConnection );
        connect( node, &TextureNode::textureInUse, m_renderThread, &RenderThread::renderNext, Qt::QueuedConnection );

        // Get the production of FBO textures started..
        QMetaObject::invokeMethod( m_renderThread, "renderNext", Qt::QueuedConnection );
    }

    node->setRect( boundingRect() );

    return node;
}
