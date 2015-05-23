#ifndef BRICK_H
#define BRICK_H

#include <QGLContext>
#include "Object.h"

class Brick : public Object
{
public:
    Brick();
    Brick(float x, float y, float z);

    void draw();
};

#endif // BRICK_H
