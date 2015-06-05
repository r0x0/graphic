#ifndef AREA_H
#define AREA_H

#include "Object.h"

class Area : public Object
{
public:
    Area();
    Area(float x, float y, float z);
    void draw();
    void movePosition(float x, float y, float z){}

};

#endif // AREA_H
