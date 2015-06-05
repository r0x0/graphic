#ifndef BRICK_H
#define BRICK_H

#include <QGLFunctions>
#include <QtOpenGL>
#include "Object.h"


class Brick : public Object
{

public:
    Brick();
    Brick(float x, float y, float z);

    void draw();
    void movePosition(float x, float y, float z);

private:
    GLuint  texture[3];                             // Storage for 3 textures

};

#endif // BRICK_H
