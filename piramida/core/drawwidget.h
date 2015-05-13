#ifndef DRAWWIDGET_H
#define DRAWWIDGET_H

#include <QOpenGLWidget>
#include <QMouseEvent>
#include <QMatrix>
#include <QOpenGLContext>
#include <QOpenGLFunctions>

class DrawWidget : public QOpenGLWidget, protected QOpenGLFunctions
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

    QVector <QVector3D> vertices;
    QMatrix4x4 m_projection;
    QOpenGLContext *m_context;

};

#endif // DRAWWIDGET_H
