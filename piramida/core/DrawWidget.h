#ifndef DRAWWIDGET_H
#define DRAWWIDGET_H

#include <QGLWidget>
#include <QMouseEvent>
#include <QGLContext>
#include <QGLFunctions>
#include <QMatrix4x4>
#include <QGLFramebufferObject>

#include "../graphic/World.h"


class DrawWidget : public QGLWidget, protected QGLFunctions
{
    Q_OBJECT
public:
    explicit DrawWidget(QWidget *parent = 0);
    ~DrawWidget();

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

//    QSize minimumSizeHint() const;
//    QSize sizeHint() const;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

signals:
    void xRotationChanged(int angle);
    void yRotationChanged(int angle);
    void zRotationChanged(int angle);

public slots:
    void setZRotation(int angle);
    void setYRotation(int angle);
    void setXRotation(int angle);

private:



    void draw();
    static void qNormalizeAngle(int &angle);

    int xRot;
    int yRot;
    int zRot;

    QPoint lastPos;

    GLuint pbufferList;
    int timerId;

    GLuint  filter;                                 // Which Filter To Use
    GLuint  texture[3];                             // Storage for 3 textures

    QGLFramebufferObject *fbo;

    void drawCube(int i, GLfloat z, GLfloat rotation, GLfloat jmp, GLfloat amp);
    void drawAxis();

    GLuint axes_list;
GLint cubeTexture;
    World *world;
    void prepareGl();
};

#endif // DRAWWIDGET_H
