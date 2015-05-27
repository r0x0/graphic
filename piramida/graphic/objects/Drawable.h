#ifndef DRAWABLE_H
#define DRAWABLE_H


class Drawable
{
public:
    virtual ~Drawable(){}
    virtual void draw() = 0;
};

#endif // DRAWABLE_H
