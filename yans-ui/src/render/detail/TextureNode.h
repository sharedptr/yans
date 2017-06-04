#pragma once
#ifndef YANS_UI_RENDER_DETAIL_TEXTURENODE_H_
#define YANS_UI_RENDER_DETAIL_TEXTURENODE_H_

#include "yans-ui.h"

#include <QMutex>
#include <QObject>
#include <QSGSimpleTextureNode>

class QQuickWindow;

YANS_UNS_B2( render, detail )

class Q_DECL_HIDDEN TextureNode : public QObject, public QSGSimpleTextureNode
{
    Q_OBJECT

public:
    explicit TextureNode( QQuickWindow* window );
    virtual ~TextureNode();

signals:
    void textureInUse();
    void pendingNewTexture();

public slots:

    // This function gets called on the FBO rendering thread and will store the
    // texture id and size and schedule an update on the window.
    void newTexture( uint id, const QSize& size );

    // Before the scene graph starts to render, we update to the pending texture
    void prepareNode();

private:
    uint m_id;
    QSize m_size;

    QMutex m_mutex;

    QSGTexture* m_texture;
    QQuickWindow* m_window;
};

YANS_UNS_E2( render, detail )

#endif // YANS_UI_RENDER_DETAIL_TEXTURENODE_H_
