#include "drawwidget.h"

#include <QDebug>

DrawWidget::DrawWidget(QWidget *parent) : QOpenGLWidget(parent)
{

}

DrawWidget::~DrawWidget()
{

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
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    f->glClearColor(0.0, 0.0, 0.0, 1.0);
    static const GLfloat vertex_buffer_data[] = {
        0.0, 0.8, 0.0,
        -0.8, -0.8, 0.0,
        0.8, -0.8, 0.0
    };
    f->glGenBuffers(1, &vertex_buffer);
    f->glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    f->glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);
//    qglClearColor(Qt::black);

//    glEnable(GL_DEPTH_TEST);
//    glEnable(GL_CULL_FACE);
//    glShadeModel(GL_SMOOTH);
//    glEnable(GL_LIGHTING);
//    glEnable(GL_LIGHT0);

//    shaderProgram.addShaderFromSourceFile(QGLShader::Vertex, ":/vertexShader.vsh");
//    shaderProgram.addShaderFromSourceFile(QGLShader::Fragment, ":/fragmentShader.fsh");
//    shaderProgram.link();
//    vertices << QVector3D(1, 0, -2) << QVector3D(0, 1, -2) << QVector3D(-1, 0, -2);

//    initializeOpenGLFunctions();
//    static GLfloat lightPosition[4] = { 0, 0, 10, 1.0 };
//    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
}

void DrawWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -10.0);
    glRotatef(xRot / 16.0, 1.0, 0.0, 0.0);
    glRotatef(yRot / 16.0, 0.0, 1.0, 0.0);
    glRotatef(zRot / 16.0, 0.0, 0.0, 1.0);
    draw();
}

void DrawWidget::resizeGL(int width, int height)
{
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    f->glViewport(0, 0, width, height);
//    if (height == 0) {
//    height = 1;
//    }
//    pMatrix.setToIdentity();
//    pMatrix.perspective(60.0, (float) width / (float) height, 0.001, 1000);
//    glViewport(0, 0, width, height);

//    int side = qMin(width, height);
//    glViewport((width - side) / 2, (height - side) / 2, side, side);

//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//#ifdef QT_OPENGL_ES_1
//    glOrthof(-2, +2, -2, +2, 1.0, 15.0);
//#else
//    glOrtho(-2, +2, -2, +2, 1.0, 15.0);
//#endif
//    glMatrixMode(GL_MODELVIEW);
}

//QSize DrawWidget::minimumSizeHint() const
//{
//    return QSize(200, 200);
//}

//QSize DrawWidget::sizeHint() const
//{
//    return QSize(800, 600);
//}

void DrawWidget::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}

void DrawWidget::mouseMoveEvent(QMouseEvent *event)
{
//    int dx = event->x() - lastPos.x();
//    int dy = event->y() - lastPos.y();

//    if (event->buttons() & Qt::LeftButton) {
//        setXRotation(xRot + 8 * dy);
//        setYRotation(yRot + 8 * dx);
//    } else if (event->buttons() & Qt::RightButton) {
//        setXRotation(xRot + 8 * dy);
//        setZRotation(zRot + 8 * dx);
//    }

//    lastPos = event->pos();
}

void DrawWidget::draw()
{
//    glc(Qt::red);
    glBegin(GL_QUADS);
       glNormal3f(0,0,-1);
       glVertex3f(-1,-1,0);
       glVertex3f(-1,1,0);
       glVertex3f(1,1,0);
       glVertex3f(1,-1,0);

    glEnd();
    glBegin(GL_TRIANGLES);
       glNormal3f(0,-1,0.707);
       glVertex3f(-1,-1,0);
       glVertex3f(1,-1,0);
       glVertex3f(0,0,1.2);
    glEnd();
    glBegin(GL_TRIANGLES);
       glNormal3f(1,0, 0.707);
       glVertex3f(1,-1,0);
       glVertex3f(1,1,0);
       glVertex3f(0,0,1.2);
    glEnd();
    glBegin(GL_TRIANGLES);
       glNormal3f(0,1,0.707);
       glVertex3f(1,1,0);
       glVertex3f(-1,1,0);
       glVertex3f(0,0,1.2);
    glEnd();
    glBegin(GL_TRIANGLES);
       glNormal3f(-1,0,0.707);
       glVertex3f(-1,1,0);
       glVertex3f(-1,-1,0);
       glVertex3f(0,0,1.2);
    glEnd();
}

