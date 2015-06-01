#ifndef DRAWWIDGET_H
#define DRAWWIDGET_H

#include <QGLWidget>
#include <QMouseEvent>
#include <QGLContext>
#include <QGLFunctions>
#include <QMatrix4x4>
#include <QGLFramebufferObject>

#include <QTimer>

#include "../graphic/World.h"
#include "../graphic/objects/Textures.h"


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

    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);

signals:

public slots:
    void blender();
    void turnOnOffLight();
    void moveUp();
    void moveBack();
    void moveRight();
    void moveLeft();

private:

    void draw();
    static void qNormalizeAngle(int &angle);
    void loadTextures();
    void prepareGl();

//    KEYS CONTROLS
    bool blend = false;
    bool light = true;

    float xRot = 0 ;
    float yRot = 0 ;
    float zRot = 0 ;

    float xCam = 0;
    float yCam = 0;
    float zCam = -10.0f;
    float zoom = 5.0f;

    QPoint lastPos;

    GLuint pbufferList;
    int timerId;

    GLuint  filter;                                 // Which Filter To Use


    QGLFramebufferObject *fbo;

    GLuint axes_list;
    GLint cubeTexture;
    World *world;
    Textures * textures;

    QTimer * updater = new QTimer();

};

#endif // DRAWWIDGET_H
