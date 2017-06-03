#include "RenderThread.h"

#include "render/private/LogoRenderer.h"
#include "render/ThreadRenderer.h"

#include <QOffscreenSurface>
#include <QOpenGLContext>
#include <QOpenGLFramebufferObject>
#include <QOpenGLFunctions>

RenderThread::RenderThread( const QSize &size )
    : surface( 0 ), context( 0 ), m_renderFbo( 0 ), m_displayFbo( 0 ), m_logoRenderer( 0 ), m_size( size )
{
    ThreadRenderer::threads << this;
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
        m_logoRenderer = new LogoRenderer();
        m_logoRenderer->initialize();
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
    context->makeCurrent( surface );
    delete m_renderFbo;
    delete m_displayFbo;
    delete m_logoRenderer;
    context->doneCurrent();
    delete context;

    // schedule this to be deleted only after we're done cleaning up
    surface->deleteLater();

    // Stop event processing, move the thread to GUI and make sure it is deleted.
    exit();
    moveToThread( QGuiApplication::instance()->thread() );
}
