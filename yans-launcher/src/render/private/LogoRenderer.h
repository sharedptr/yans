#pragma once
#ifndef LOGORENDERER_H
#define LOGORENDERER_H

#include <QOpenGLShaderProgram>
#include <QVector3D>
#include <QVector>

class LogoRenderer
{

public:
    LogoRenderer();
    ~LogoRenderer();

    void render();

private:
    GLfloat m_Angle;
    GLfloat m_Scale;

    void paintQtLogo();
    void createGeometry();
    void quad( GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat x3, GLfloat y3, GLfloat x4, GLfloat y4 );
    void extrude( GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2 );
    void initialize();
    void beforeRender();
    void afterRender();

    QVector< QVector3D > m_Vertices;
    QVector< QVector3D > m_Normals;
    QOpenGLShaderProgram m_ShaderProgram;
    int vertexAttr1;
    int normalAttr1;
    int matrixUniform1;
    bool m_GLInit;
};

#endif // LOGORENDERER_H
