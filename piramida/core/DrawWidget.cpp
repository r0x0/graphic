#include "DrawWidget.h"

#include <QDebug>
#include <math.h>



GLfloat LightAmbient[]= { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat LightDiffuse[]= { 1.0f, 1.0f, 1.0f, 0.2f };
GLfloat LightPosition[]= { 0.0f, 0.0f, 2.0f, 1.0f };

QGLFormat desiredFormat()
{
    QGLFormat fmt;
    fmt.setSwapInterval(1);
    return fmt;
}

DrawWidget::DrawWidget(QWidget *parent) : QGLWidget(desiredFormat(), parent) {
    setMouseTracking(true);
    prepareGl();
    world = new World();
}

void DrawWidget::prepareGl(){
    // create the framebuffer object - make sure to have a current
    // context before creating it
    makeCurrent();
    fbo = new QGLFramebufferObject(512, 512);
    timerId = startTimer(50);

    connect(updater, SIGNAL(timeout()), this, SLOT(updateGL()));
    if(format().swapInterval() == -1)
        {
            // V_blank synchronization not available (tearing likely to happen)
            qDebug("Swap Buffers at v_blank not available: refresh at approx 60fps.");
            updater->setInterval(17);
        }
        else
        {
            // V_blank synchronization available
            updater->setInterval(0);
        }
        updater->start();
}

DrawWidget::~DrawWidget()
{
    glDeleteLists(pbufferList, 1);
    delete fbo;
}

void DrawWidget::initializeGL()
{

    loadTextures();

    glEnable(GL_TEXTURE_2D);                            // Enable Texture Mapping
    glShadeModel(GL_SMOOTH);                            // Enable Smooth Shading
    glClearColor(0.0f, 0.0f, 0.2f, 0.5f);               // Black Background
    glClearDepth(1.0f);                                 // Depth Buffer Setup
    glEnable(GL_DEPTH_TEST);                            // Enables Depth Testing

    glDepthFunc(GL_LEQUAL);                             // The Type Of Depth Testing To Do

    glColor4f(1.0f,1.0f,1.0f,0.5f);         // Full Brightness, 50% Alpha ( NEW )
    glBlendFunc(GL_SRC_ALPHA,GL_ONE);       // Blending Function For Translucency Based On Source Alpha Value ( NEW )

    glMatrixMode(GL_PROJECTION);
     glLoadIdentity();				// Reset The Projection Matrix

    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Really Nice Perspective

    glMatrixMode(GL_MODELVIEW);

    glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);             // Setup The Ambient Light
    glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);             // Setup The Diffuse Light
    glLightfv(GL_LIGHT1, GL_POSITION,LightPosition);            // Position The Light

    glEnable(GL_LIGHT1);                            // Enable Light One
    glEnable(GL_LIGHTING);

}

void DrawWidget::resizeGL(int w, int h)
{
    if (h==0){				// Prevent A Divide By Zero If The Window Is Too Small
        h=1;
    }

    glViewport(0, 0, w, h);		// Reset The Current Viewport And Perspective Transformation

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-5.0, 5.0, -5.0, 5.0, -15.0, 15.0);

    glMatrixMode(GL_MODELVIEW);
}

void DrawWidget::mouseMoveEvent(QMouseEvent *event)
{
    yRot += lastPos.x() - event->x();
    if(xRot < 0){
        xRot = 360 - xRot;
    } else if (xRot > 360){
        xRot = 0 + xRot;
    }

    float upDown = lastPos.y() - event->y();
//    float scale = xRot / 90;

//    yRot += xrot / 90
    zRot += upDown;
    lastPos = event->pos();
}

void DrawWidget::wheelEvent(QWheelEvent *event)
{
//    zCam += event->delta()/120;
    zoom += event->delta()/120;
    float persne = -1*zoom;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(persne, zoom, persne, zoom, -15.0, 15.0);

    glMatrixMode(GL_MODELVIEW);
}

void DrawWidget::paintGL()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);         // Clear The Screen And The Depth Buffer
    glLoadIdentity();                           // Reset The View

    glTranslatef(xCam, yCam, zCam);                      // Translate Into/Out Of The Screen By z

    glRotatef(xRot/2,1.0f,0.0f,0.0f);                     // Rotate On The X Axis By xrot
    glRotatef(yRot/2,0.0f,1.0f,0.0f);                     // Rotate On The Y Axis By yrot
    glRotatef(zRot/2,0.0f,0.0f,1.0f);                     // Rotate On The Y Axis By yrot


    glEnable(GL_TEXTURE_2D);

    world->draw();

}

void DrawWidget::loadTextures(){
    qDebug() << "Textures loading...";
    textures = new Textures();

    Texture * brick = new Texture();
    QImage brickIm = QGLWidget::convertToGLFormat( QImage(":/res/graphic/textures/cube.jpg") );
    brick->image = new QImage(brickIm.scaled(512,512,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
    textures->brickTexture = brick;
    world->loadTextures(textures);
}

void DrawWidget::blender(){
    blend = !blend;
    if(blend)
    {
        qDebug() << "Enable blender";
        glEnable(GL_BLEND);     // Turn Blending On
        glDisable(GL_DEPTH_TEST);   // Turn Depth Testing Off
    }
    else                    // Otherwise
    {
        qDebug() << "Disable blender";
        glDisable(GL_BLEND);        // Turn Blending Off
        glEnable(GL_DEPTH_TEST);    // Turn Depth Testing On
    }
}

void DrawWidget::turnOnOffLight()
{
    light = ! light;
    if (!light)             // If Not Light
    {
        qDebug() << "disable light";
        glDisable(GL_LIGHTING);     // Disable Lighting
    }
    else                    // Otherwise
    {
        qDebug() << "Enable light";
        glEnable(GL_LIGHTING);      // Enable Lighting
    }
}

void DrawWidget::moveUp()
{
    zCam-=0.1;
}

void DrawWidget::moveBack()
{
    zCam+=0.1;
}

void DrawWidget::moveRight()
{
    xCam-=0.1;
}

void DrawWidget::moveLeft()
{
    xCam+=0.1;
}
