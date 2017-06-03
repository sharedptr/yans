#pragma once
#ifndef RENDERTHREAD_H
#define RENDERTHREAD_H

#include <QGuiApplication>
#include <QSize>
#include <QThread>

class LogoRenderer;

class QOffscreenSurface;
class QOpenGLContext;
class QOpenGLFramebufferObject;

/*
 * The render thread shares a context with the scene graph and will
 * render into two separate FBOs, one to use for display and one
 * to use for rendering
 */
class RenderThread : public QThread
{
    Q_OBJECT
public:
    explicit RenderThread( const QSize &size );

    QOffscreenSurface *surface;
    QOpenGLContext *context;

public slots:
    void renderNext();
    void shutDown();

signals:
    void textureReady( int id, const QSize &size );

private:
    QOpenGLFramebufferObject *m_renderFbo;
    QOpenGLFramebufferObject *m_displayFbo;

    LogoRenderer *m_logoRenderer;
    QSize m_size;
};

#endif // RENDERTHREAD_H
