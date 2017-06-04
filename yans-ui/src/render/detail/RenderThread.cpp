#include "RenderThread.h"

#include "render/detail/GameRenderer.h"

#include <QGuiApplication>
#include <QOffscreenSurface>
#include <QOpenGLContext>
#include <QOpenGLFramebufferObject>
#include <QOpenGLFunctions>

YANS_UNS_B2( render, detail )

RenderThread::RenderThread( const QSize& size )
    : surface( nullptr ),
      context( nullptr ),
      m_renderFbo( nullptr ),
      m_displayFbo( nullptr ),
      m_logoRenderer( nullptr ),
      m_size( size )
{
}

void RenderThread::renderNext()
{
    context->makeCurrent( surface );

    if( !m_renderFbo )
    {
        // Initialize the buffers and renderer
        QOpenGLFramebufferObjectFormat format;
        format.setAttachment( QOpenGLFramebufferObject::CombinedDepthStencil );
        m_renderFbo = new QOpenGLFramebufferObject( m_size, format );
        m_displayFbo = new QOpenGLFramebufferObject( m_size, format );
        m_logoRenderer = new GameRenderer();
    }

    m_renderFbo->bind();
    context->functions()->glViewport( 0, 0, m_size.width(), m_size.height() );

    m_logoRenderer->render();

    // We need to flush the contents to the FBO before posting
    // the texture to the other thread, otherwise, we might
    // get unexpected results.
    context->functions()->glFlush();

    m_renderFbo->bindDefault();
    qSwap( m_renderFbo, m_displayFbo );

    emit textureReady( m_displayFbo->texture(), m_size );
}

void RenderThread::shutDown()
{
    if( context != nullptr )
    {
        context->makeCurrent( surface );
        delete m_renderFbo;
        delete m_displayFbo;
        delete m_logoRenderer;
        context->doneCurrent();
        delete context;
        context = nullptr;

        // schedule this to be deleted only after we're done cleaning up
        surface->deleteLater();

        // Stop event processing, move the thread to GUI and make sure it is deleted.
    }
    exit();
    moveToThread( QGuiApplication::instance()->thread() );
}

YANS_UNS_E2( render, detail )
