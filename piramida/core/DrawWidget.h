#ifndef DRAWWIDGET_H
#define DRAWWIDGET_H

#include <QGLWidget>
#include <QMouseEvent>
#include <QGLContext>
#include <QGLFunctions>
#include <QMatrix4x4>
#include <QGLFramebufferObject>
#include <QGLFunctions>
#include <GL/glu.h>

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

private slots:
    void updateCamera();

public slots:
    void blender();
    void turnOnOffLight();
    void moveUp();
    void moveBack();
    void moveRight();
    void moveLeft();
    void setFilter(int filter);
    void setFog();
    void changeFogMode();
    void chnageCamera(bool camera);

    void speedDown();
    void speedUp();
    void setFlag();

private:

    void draw();
    static void qNormalizeAngle(int &angle);
    void loadTextures();
    void prepareGl();
    float rad(float angle);
    void changeView(QPoint pos);
    void zoomView(float change);

//    KEYS CONTROLS
    bool blend = false;
    bool light = true;
    bool fog = false;
    bool cameraAuto = true;
    float zoom = 20;
    volatile bool shouldDrawFlag = false;
    int filter = 0;


    GLfloat xrot;            // x rotation
    GLfloat yrot;            // y rotation
    GLfloat xspeed;          // x rotation speed
    GLfloat yspeed;          // y rotation speed

    GLfloat walkbias = 0;
    GLfloat walkbiasangle = 0;

    GLfloat lookupdown = 0.0;
    const float piover180 = 0.0174532925f;

    float heading, xpos, zpos, ypos;

    GLfloat therotate;

    GLfloat z=0.0f;                       // depth into the screen.

    QPoint lastPos;

    GLuint pbufferList;
    int timerId;
    GLuint fogfilter= 0;                    // Which Fog To Use
    QGLFramebufferObject *fbo;

    GLuint axes_list;
    World *world;
    Textures * textures;

    QTimer * updater = new QTimer();
    QTimer * cameraUpdater = new QTimer();
    QMutex cameraMutex;

    float zoomValue =0.02;
    int moveCount = 0;
    int cameraCount = 0;

    void drawFlag();
};

#endif // DRAWWIDGET_H
