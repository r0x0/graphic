#ifndef OBJECT_H
#define OBJECT_H

#include "Drawable.h"
#include <QMutex>
#include <QMutexLocker>

class Object : public Drawable
{

public:
    Object(float x, float y, float z) : x(x),y(y),z(z){}
    virtual ~Object(){}

    virtual void movePosition(float x, float y, float z) = 0;

    volatile float x;
    volatile float y;
    volatile float z;

    volatile float rotX;
    volatile float rotY;
    volatile float rotZ;

    volatile float scale;

protected:
    QMutex mutexObj;

};

#endif // OBJECT_H
