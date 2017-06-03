#include "TextureNode.h"

#include <QMutexLocker>

TextureNode::TextureNode( QQuickWindow *window ) : m_id( 0 ), m_size( 0, 0 ), m_texture( 0 ), m_window( window )
{
    // Our texture node must have a texture, so use the default 0 texture.
    m_texture = m_window->createTextureFromId( 0, QSize( 1, 1 ) );
    setTexture( m_texture );
    setFiltering( QSGTexture::Linear );
}

TextureNode::~TextureNode()
{
    delete m_texture;
}

void TextureNode::newTexture( uint id, const QSize &size )
{
    {
        QMutexLocker locker( &m_mutex );
        m_id = id;
        m_size = size;
    }
    // We cannot call QQuickWindow::update directly here, as this is only allowed
    // from the rendering thread or GUI thread.
    emit pendingNewTexture();
}

void TextureNode::prepareNode()
{
    uint newId{0};
    QSize size{0, 0};
    {
        QMutexLocker locker( &m_mutex );
        newId = m_id;
        size = m_size;
        m_id = 0;
    }

    if( newId != 0 )
    {
        delete m_texture;
        // note: include QQuickWindow::TextureHasAlphaChannel if the rendered content
        // has alpha.
        m_texture = m_window->createTextureFromId( newId, size );
        setTexture( m_texture );

        markDirty( DirtyMaterial );

        // This will notify the rendering thread that the texture is now being rendered
        // and it can start rendering to the other one.
        emit textureInUse();
    }
}
