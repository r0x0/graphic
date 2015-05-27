#ifndef OBJECT_H
#define OBJECT_H

#include "Drawable.h"

class Object : public Drawable
{
public:
    Object(float x, float y, float z) : x(x),y(y),z(z){}
    virtual ~Object(){}

    volatile float x;
    volatile float y;
    volatile float z;

    volatile float rotX;
    volatile float rotY;
    volatile float rotZ;

    volatile float scale;
};

#endif // OBJECT_H
