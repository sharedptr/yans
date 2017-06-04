#include "GameRenderer.h"

#include <QMatrix4x4>

#include <cmath>

YANS_UNS_B2( render, detail )

GameRenderer::GameRenderer() : m_GLInit( false )
{
}

GameRenderer::~GameRenderer()
{
}

void GameRenderer::paintQtLogo()
{
    m_ShaderProgram.enableAttributeArray( normalAttr1 );
    m_ShaderProgram.enableAttributeArray( vertexAttr1 );
    m_ShaderProgram.setAttributeArray( vertexAttr1, m_Vertices.constData() );
    m_ShaderProgram.setAttributeArray( normalAttr1, m_Normals.constData() );
    glDrawArrays( GL_TRIANGLES, 0, m_Vertices.size() );
    m_ShaderProgram.disableAttributeArray( normalAttr1 );
    m_ShaderProgram.disableAttributeArray( vertexAttr1 );
}

void GameRenderer::render()
{
    beforeRender();

    m_Angle += 1.0f;

    QMatrix4x4 modelview;
    modelview.rotate( m_Angle, 0.0f, 1.0f, 0.0f );
    modelview.rotate( m_Angle, 1.0f, 0.0f, 0.0f );
    modelview.rotate( m_Angle, 0.0f, 0.0f, 1.0f );
    modelview.scale( m_Scale );
    modelview.translate( 0.0f, -0.2f, 0.0f );

    m_ShaderProgram.bind();
    m_ShaderProgram.setUniformValue( matrixUniform1, modelview );
    paintQtLogo();
    m_ShaderProgram.release();

    afterRender();
}

void GameRenderer::createGeometry()
{
    m_Vertices.clear();
    m_Normals.clear();

    constexpr GLfloat x1 = +0.06f;
    constexpr GLfloat y1 = -0.14f;
    constexpr GLfloat x2 = +0.14f;
    constexpr GLfloat y2 = -0.06f;
    constexpr GLfloat x3 = +0.08f;
    constexpr GLfloat y3 = +0.00f;
    constexpr GLfloat x4 = +0.30f;
    constexpr GLfloat y4 = +0.22f;

    quad( x1, y1, x2, y2, y2, x2, y1, x1 );
    quad( x3, y3, x4, y4, y4, x4, y3, x3 );

    extrude( x1, y1, x2, y2 );
    extrude( x2, y2, y2, x2 );
    extrude( y2, x2, y1, x1 );
    extrude( y1, x1, x1, y1 );
    extrude( x3, y3, x4, y4 );
    extrude( x4, y4, y4, x4 );
    extrude( y4, x4, y3, x3 );

    constexpr GLfloat Pi = 3.14159f;
    constexpr int NumSectors = 100;

    for( int i = 0; i < NumSectors; ++i )
    {
        GLfloat angle1 = ( i * 2 * Pi ) / NumSectors;
        GLfloat x5 = 0.30f * std::sin( angle1 );
        GLfloat y5 = 0.30f * std::cos( angle1 );
        GLfloat x6 = 0.20f * std::sin( angle1 );
        GLfloat y6 = 0.20f * std::cos( angle1 );

        GLfloat angle2 = ( ( i + 1 ) * 2 * Pi ) / NumSectors;
        GLfloat x7 = 0.20f * std::sin( angle2 );
        GLfloat y7 = 0.20f * std::cos( angle2 );
        GLfloat x8 = 0.30f * std::sin( angle2 );
        GLfloat y8 = 0.30f * std::cos( angle2 );

        quad( x5, y5, x6, y6, x7, y7, x8, y8 );

        extrude( x6, y6, x7, y7 );
        extrude( x8, y8, x5, y5 );
    }

    for( auto& vertex : m_Vertices )
    {
        vertex *= 2.0f;
    }
}

void GameRenderer::quad( GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat x3, GLfloat y3, GLfloat x4,
                         GLfloat y4 )
{
    m_Vertices << QVector3D( x1, y1, -0.05f );
    m_Vertices << QVector3D( x2, y2, -0.05f );
    m_Vertices << QVector3D( x4, y4, -0.05f );

    m_Vertices << QVector3D( x3, y3, -0.05f );
    m_Vertices << QVector3D( x4, y4, -0.05f );
    m_Vertices << QVector3D( x2, y2, -0.05f );

    QVector3D n = QVector3D::normal( QVector3D( x2 - x1, y2 - y1, 0.0f ), QVector3D( x4 - x1, y4 - y1, 0.0f ) );

    m_Normals << n;
    m_Normals << n;
    m_Normals << n;

    m_Normals << n;
    m_Normals << n;
    m_Normals << n;

    m_Vertices << QVector3D( x4, y4, 0.05f );
    m_Vertices << QVector3D( x2, y2, 0.05f );
    m_Vertices << QVector3D( x1, y1, 0.05f );

    m_Vertices << QVector3D( x2, y2, 0.05f );
    m_Vertices << QVector3D( x4, y4, 0.05f );
    m_Vertices << QVector3D( x3, y3, 0.05f );

    n = QVector3D::normal( QVector3D( x2 - x4, y2 - y4, 0.0f ), QVector3D( x1 - x4, y1 - y4, 0.0f ) );

    m_Normals << n;
    m_Normals << n;
    m_Normals << n;

    m_Normals << n;
    m_Normals << n;
    m_Normals << n;
}

void GameRenderer::extrude( GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2 )
{
    m_Vertices << QVector3D( x1, y1, +0.05f );
    m_Vertices << QVector3D( x2, y2, +0.05f );
    m_Vertices << QVector3D( x1, y1, -0.05f );

    m_Vertices << QVector3D( x2, y2, -0.05f );
    m_Vertices << QVector3D( x1, y1, -0.05f );
    m_Vertices << QVector3D( x2, y2, +0.05f );

    const QVector3D n = QVector3D::normal( QVector3D( x2 - x1, y2 - y1, 0.0f ), QVector3D( 0.0f, 0.0f, -0.1f ) );

    m_Normals << n;
    m_Normals << n;
    m_Normals << n;

    m_Normals << n;
    m_Normals << n;
    m_Normals << n;
}

void GameRenderer::initialize()
{
    glClearColor( 0.1f, 0.1f, 0.2f, 1.0f );

    m_ShaderProgram.addShaderFromSourceFile( QOpenGLShader::Vertex, ":/shaders/simple.vert" );
    m_ShaderProgram.addShaderFromSourceFile( QOpenGLShader::Fragment, ":/shaders/simple.frag" );
    m_ShaderProgram.link();

    vertexAttr1 = m_ShaderProgram.attributeLocation( "vertex" );
    normalAttr1 = m_ShaderProgram.attributeLocation( "normal" );
    matrixUniform1 = m_ShaderProgram.uniformLocation( "matrix" );

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    m_Angle = 0.0f;
    m_Scale = 1.0f;
    createGeometry();

    m_GLInit = true;
}

void GameRenderer::beforeRender()
{
    if( Q_UNLIKELY( !m_GLInit ) )
    {
        initialize();
    }

    glDepthMask( true );

    glClearColor( 0.0f, 0.0f, 1.0f, 1.0f );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    glFrontFace( GL_CW );
    glCullFace( GL_FRONT );
    glEnable( GL_CULL_FACE );
    glEnable( GL_DEPTH_TEST );
}

void GameRenderer::afterRender()
{
    glDisable( GL_DEPTH_TEST );
    glDisable( GL_CULL_FACE );
}

YANS_UNS_E2( render, detail )
