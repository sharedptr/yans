#pragma once
#ifndef TEXTURENODE_H
#define TEXTURENODE_H

#include <QMutex>
#include <QObject>
#include <QQuickWindow>
#include <QSGSimpleTextureNode>

class TextureNode : public QObject, public QSGSimpleTextureNode
{
    Q_OBJECT

public:
    explicit TextureNode( QQuickWindow *window );
    virtual ~TextureNode();

signals:
    void textureInUse();
    void pendingNewTexture();

public slots:

    // This function gets called on the FBO rendering thread and will store the
    // texture id and size and schedule an update on the window.
    void newTexture( uint id, const QSize &size );

    // Before the scene graph starts to render, we update to the pending texture
    void prepareNode();

private:
    uint m_id;
    QSize m_size;

    QMutex m_mutex;

    QSGTexture *m_texture;
    QQuickWindow *m_window;
};

#endif // TEXTURENODE_H
