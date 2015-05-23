#ifndef OBJECT_H
#define OBJECT_H

class Object
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

    virtual void draw() = 0;
};

#endif // OBJECT_H
