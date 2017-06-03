#include "LogoRenderer.h"

#include <QMatrix4x4>

#include <cmath>

LogoRenderer::LogoRenderer() : m_GLInit( false )
{
}

LogoRenderer::~LogoRenderer()
{
}

void LogoRenderer::paintQtLogo()
{
    m_ShaderProgram.enableAttributeArray( normalAttr1 );
    m_ShaderProgram.enableAttributeArray( vertexAttr1 );
    m_ShaderProgram.setAttributeArray( vertexAttr1, m_Vertices.constData() );
    m_ShaderProgram.setAttributeArray( normalAttr1, m_Normals.constData() );
    glDrawArrays( GL_TRIANGLES, 0, m_Vertices.size() );
    m_ShaderProgram.disableAttributeArray( normalAttr1 );
    m_ShaderProgram.disableAttributeArray( vertexAttr1 );
}

void LogoRenderer::render()
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

void LogoRenderer::createGeometry()
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

    for( auto &vertex : m_Vertices )
    {
        vertex *= 2.0f;
    }
}

void LogoRenderer::quad( GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat x3, GLfloat y3, GLfloat x4,
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

void LogoRenderer::extrude( GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2 )
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

void LogoRenderer::initialize()
{
    glClearColor( 0.1f, 0.1f, 0.2f, 1.0f );

    QOpenGLShader *vshader1 = new QOpenGLShader( QOpenGLShader::Vertex, &m_ShaderProgram );
    const char *vsrc1 = "attribute highp vec4 vertex;\n"
                        "attribute mediump vec3 normal;\n"
                        "uniform mediump mat4 matrix;\n"
                        "varying mediump vec4 color;\n"
                        "void main(void)\n"
                        "{\n"
                        "    vec3 toLight = normalize(vec3(0.0, 0.3, 1.0));\n"
                        "    float angle = max(dot(normal, toLight), 0.0);\n"
                        "    vec3 col = vec3(0.40, 1.0, 0.0);\n"
                        "    color = vec4(col * 0.2 + col * 0.8 * angle, 1.0);\n"
                        "    color = clamp(color, 0.0, 1.0);\n"
                        "    gl_Position = matrix * vertex;\n"
                        "}\n";
    vshader1->compileSourceCode( vsrc1 );

    QOpenGLShader *fshader1 = new QOpenGLShader( QOpenGLShader::Fragment, &m_ShaderProgram );
    const char *fsrc1 = "varying mediump vec4 color;\n"
                        "void main(void)\n"
                        "{\n"
                        "    gl_FragColor = color;\n"
                        "}\n";
    fshader1->compileSourceCode( fsrc1 );

    m_ShaderProgram.addShader( vshader1 );
    m_ShaderProgram.addShader( fshader1 );
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

void LogoRenderer::beforeRender()
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

void LogoRenderer::afterRender()
{
    glDisable( GL_DEPTH_TEST );
    glDisable( GL_CULL_FACE );
}
