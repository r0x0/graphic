#include "DrawWidget.h"

#include <QDebug>
#include <math.h>



GLfloat LightAmbient[]= { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat LightDiffuse[]= { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat LightPosition[]= { 0.0f, 0.0f, 10.0f, 1.0f };

DrawWidget::DrawWidget(QWidget *parent) : QGLWidget(QGLFormat(QGL::SampleBuffers), parent) {
    prepareGl();
    world = new World();
}

void DrawWidget::prepareGl(){
    // create the framebuffer object - make sure to have a current
    // context before creating it
    makeCurrent();
    fbo = new QGLFramebufferObject(512, 512);
    timerId = startTimer(20);
}

DrawWidget::~DrawWidget()
{
    glDeleteLists(pbufferList, 1);
    delete fbo;
}

void DrawWidget::qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360)
        angle -= 360 * 16;
}

void DrawWidget::setXRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != xRot) {
        xRot = angle;
        emit xRotationChanged(angle);
        update();
    }
}

void DrawWidget::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != yRot) {
        yRot = angle;
        emit yRotationChanged(angle);
        update();
    }
}

void DrawWidget::setZRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != zRot) {
        zRot = angle;
        emit zRotationChanged(angle);
        update();
    }
}

void DrawWidget::initializeGL()
{

        glEnable(GL_TEXTURE_2D);                            // Enable Texture Mapping
        glShadeModel(GL_SMOOTH);                            // Enable Smooth Shading
        glClearColor(0.0f, 0.0f, 0.2f, 0.5f);               // Black Background
        glClearDepth(1.0f);                                 // Depth Buffer Setup
        glEnable(GL_DEPTH_TEST);                            // Enables Depth Testing
        glDepthFunc(GL_LEQUAL);                             // The Type Of Depth Testing To Do
        glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Really Nice Perspective


        cubeTexture = bindTexture(QImage(":res/graphic/textures/cube.jpg"));
        //    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    gluPerspective(50.0, 1.0, 3.0, 7.0);

//    glMatrixMode(GL_MODELVIEW);
//    glEnable(GL_CULL_FACE);

//    glEnableClientState(GL_VERTEX_ARRAY);
//    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
//    glVertexPointer(3, GL_INT, 0, cubeArray);
//    glTexCoordPointer(2, GL_INT, 0, cubeTextureArray);
//    glColorPointer(4, GL_UNSIGNED_BYTE, 0, colorArray);

//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//    glEnable(GL_BLEND);
//    glEnable(GL_TEXTURE_2D);
//    glEnable(GL_DEPTH_TEST);

//    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
//    pbufferList = glGenLists(1);
//    glNewList(pbufferList, GL_COMPILE);
//    {
//        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

//        // draw cube background
//        glPushMatrix();
//        glLoadIdentity();
//        glTranslatef(0.5f, 0.5f, -2.0f);
//        glDisable(GL_TEXTURE_2D);
//        glEnableClientState(GL_COLOR_ARRAY);
////        glVertexPointer(2, GL_INT, 0, faceArray);
////        glDrawArrays(GL_QUADS, 0, 4);
//        glVertexPointer(3, GL_INT, 0, cubeArray);
//        glDisableClientState(GL_COLOR_ARRAY);
//        glEnable(GL_TEXTURE_2D);
//        glPopMatrix();

//        // draw cube
//        glTranslatef(0.5f, 0.5f, 0.5f);
//        glRotatef(1.0f, 1.0f, 1.0f, 1.0f);
//        glTranslatef(-0.5f, -0.5f, -0.5f);
//        glColor4f(0.9f, 0.9f, 0.9f, 1.0f);
//        glDrawArrays(GL_QUADS, 0, 24);

//        glPushMatrix(); // this state is popped back in the paintGL() function
//    }
//    glEndList();

    /* In some initialisation function... */

        /* Create a display list for drawing axes */
        axes_list = glGenLists(1);
        glNewList(axes_list, GL_COMPILE);

        glColor4ub(0, 0, 255, 255);
        glBegin(GL_LINE_STRIP);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(1.0f, 0.0f, 0.0f);
        glVertex3f(0.75f, 0.25f, 0.0f);
        glVertex3f(0.75f, -0.25f, 0.0f);
        glVertex3f(1.0f, 0.0f, 0.0f);
        glVertex3f(0.75f, 0.0f, 0.25f);
        glVertex3f(0.75f, 0.0f, -0.25f);
        glVertex3f(1.0f, 0.0f, 0.0f);
        glEnd();
        glBegin(GL_LINE_STRIP);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 1.0f, 0.0f);
        glVertex3f(0.0f, 0.75f, 0.25f);
        glVertex3f(0.0f, 0.75f, -0.25f);
        glVertex3f(0.0f, 1.0f, 0.0f);
        glVertex3f(0.25f, 0.75f, 0.0f);
        glVertex3f(-0.25f, 0.75f, 0.0f);
        glVertex3f(0.0f, 1.0f, 0.0f);
        glEnd();
        glBegin(GL_LINE_STRIP);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 1.0f);
        glVertex3f(0.25f, 0.0f, 0.75f);
        glVertex3f(-0.25f, 0.0f, 0.75f);
        glVertex3f(0.0f, 0.0f, 1.0f);
        glVertex3f(0.0f, 0.25f, 0.75f);
        glVertex3f(0.0f, -0.25f, 0.75f);
        glVertex3f(0.0f, 0.0f, 1.0f);
        glEnd();

        glColor4ub(255, 255, 0, 255);
//        glRasterPos3f(1.1f, 0.0f, 0.0f);
//        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, 'x');
//        glRasterPos3f(0.0f, 1.1f, 0.0f);
//        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, 'y');
//        glRasterPos3f(0.0f, 0.0f, 1.1f);
//        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, 'z');

        glEndList();



    glPushMatrix(); // push to avoid stack underflow in the first paintGL() call
}

void DrawWidget::resizeGL(int w, int h)
{
//    glViewport(0, 0, w, h);
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    float aspect = w/(float)(h ? h : 1);
//    glFrustum(-aspect, aspect, -1, 1, 10, 100);
//    glTranslatef(-0.5f, -0.5f, -0.5f);
//    glTranslatef(0.0f, 0.0f, -15.0f);
}

void DrawWidget::mousePressEvent(QMouseEvent *event)
{

}

void DrawWidget::mouseMoveEvent(QMouseEvent *event)
{

}

void DrawWidget::paintGL()
{
//    glPopMatrix(); // pop the matrix pushed in the pbuffer list

//    // push the projection matrix and the entire GL state before
//    // doing any rendering into our framebuffer object
//    glPushAttrib(GL_ALL_ATTRIB_BITS);
//    glMatrixMode(GL_PROJECTION);
//    glPushMatrix();

//    glViewport(0, 0, fbo->size().width(), fbo->size().height());
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    glOrtho(1, 1, 1, 1, -99, 99);
//    glTranslatef(0.0f, 0.0f, 0.0f);
//    glMatrixMode(GL_MODELVIEW);

//    // render to the framebuffer object
//    fbo->bind();
//    glBindTexture(GL_TEXTURE_2D, cubeTexture);
//    glCallList(pbufferList);
//    fbo->release();

//    // pop the projection matrix and GL state back for rendering
//    // to the actual widget
//    glPopAttrib();
//    glMatrixMode(GL_PROJECTION);
//    glPopMatrix();

//    glBindTexture(GL_TEXTURE_2D, fbo->texture());
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//    // draw the background
//    glMatrixMode(GL_MODELVIEW);
//    glPushMatrix();
//    glLoadIdentity();
//    glMatrixMode(GL_PROJECTION);
//    glPushMatrix();
//    glLoadIdentity();

////    glVertexPointer(2, GL_INT, 0, faceArray);
////    glTranslatef(-1.2f, -0.8f, 0.0f);
//    glScalef(0.2f, 0.2f, 0.2f);
//    for (int y = 0; y < 5; ++y) {
//        for (int x = 0; x < 5; ++x) {
////            glTranslatef(2.0f, 0, 0);
//            glColor4f(0.8f, 0.8f, 0.8f, 1.0f);
//            glDrawArrays(GL_QUADS, 0, 4);
//        }
////        glTranslatef(-10.0f, 2.0f, 0);
//    }
//    glVertexPointer(3, GL_INT, 0, cubeArray);

    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    // draw the bouncing cubes
    drawCube(0, 0.0f, 1.5f, 2.5f, 1.5f);
//    drawCube(1, 1.0f, 2.0f, 2.5f, 2.0f);
//    drawCube(2, 2.0f, 3.5f, 2.5f, 2.5f);
    glPopMatrix();

    drawAxis();
}

void DrawWidget::drawAxis(){
    /* In my display function */

        /* Draw axes */
        glPushMatrix();
        glCallList(axes_list);
        glPopMatrix();

//        QPainter p(this);
//            p.drawText(0, 0, "X");
//            p.drawText(0, 0, "Y");
//            p.drawText(0, 0, "Z");
//            p.end();
}

void DrawWidget::drawCube(int i, GLfloat z, GLfloat rotation, GLfloat jmp, GLfloat amp)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
//    glTranslatef(xOffs[i], yOffs[i], z);
//    glTranslatef(0.5f, 0.5f, 0.5f);
//    GLfloat scale = 0.75 + i*(0.25f/2);
//    glScalef(scale, scale, scale);
//    glRotatef(rot[i], 1.0f, 1.0f, 1.0f);
//    glTranslatef(-0.5f, -0.5f, -0.5f);

    glColor4f(1.0f, 1.0f, 1.0f, 0.8f);
    glDrawArrays(GL_QUADS, 0, 24);

//    if (xOffs[i] > 1.0f || xOffs[i] < -1.0f) {
//        xInc[i] = -xInc[i];
//        xOffs[i] = xOffs[i] > 1.0f ? 1.0f : -1.0f;
//    }
//    xOffs[i] += xInc[i];
//    yOffs[i] = qAbs(cos((-3.141592f * jmp) * xOffs[i]) * amp) - 1;
//    rot[i] += rotation;
}

