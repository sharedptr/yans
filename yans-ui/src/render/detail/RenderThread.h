#pragma once
#ifndef YANS_UI_RENDER_DETAIL_RENDERTHREAD_H_
#define YANS_UI_RENDER_DETAIL_RENDERTHREAD_H_

#include "yans-ui.h"

#include <QSize>
#include <QThread>

class QOffscreenSurface;
class QOpenGLContext;
class QOpenGLFramebufferObject;

YANS_UNS_B2( render, detail )

class GameRenderer;

/*
 * The render thread shares a context with the scene graph and will
 * render into two separate FBOs, one to use for display and one
 * to use for rendering
 */
class Q_DECL_HIDDEN RenderThread : public QThread
{
    Q_OBJECT
public:
    explicit RenderThread( const QSize& size );

    QOffscreenSurface* surface;
    QOpenGLContext* context;

public slots:
    void renderNext();
    void shutDown();

signals:
    void textureReady( uint id, const QSize& size );

private:
    QOpenGLFramebufferObject* m_renderFbo;
    QOpenGLFramebufferObject* m_displayFbo;

    GameRenderer* m_logoRenderer;
    QSize m_size;
};

YANS_UNS_E2( render, detail )

#endif // YANS_UI_RENDER_DETAIL_RENDERTHREAD_H_
