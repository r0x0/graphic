#ifndef GRAPHICWIDGET_H
#define GRAPHICWIDGET_H

#include <QGLWidget>
#include "includeGL.h"

class GraphicWidget : public QGLWidget {

    Q_OBJECT

    QFont *qfont;

public:
    GraphicWidget(QWidget *parent = 0);
    ~GraphicWidget(){}

    QSize minimumSizeHint() const;
    QSize sizeHint() const;

protected:
    void resizeGL(int width, int height);
    void paintGL();
    void initializeGL();

};

#endif // GRAPHICWIDGET_H
