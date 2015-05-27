#ifndef WORLD_H
#define WORLD_H


#include "objects/Brick.h"
#include "objects/Area.h"
#include "objects/Drawable.h"

#include <QGLContext>
#include <QGLFunctions>
#include <QtOpenGL>
#include <QDebug>
#include <QGLFramebufferObject>
#include <QtGui/QImage>

class World : public Drawable
{
    Q_OBJECT

public:
    World();

    void draw();
    void init();

private:

private:

};

#endif // WORLD_H
