#ifndef TEXTURE_H
#define TEXTURE_H

#include <QImage>
#include <QtOpenGL>

class Texture
{

public:
    Texture();
    ~Texture();

    GLuint texture[3];
    QImage *image;
};

#endif // TEXTURES_H
