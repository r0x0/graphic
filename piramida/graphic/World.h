#ifndef WORLD_H
#define WORLD_H

#include <list>

#include "objects/Brick.h"
#include "objects/Area.h"
#include "objects/Drawable.h"
#include "objects/Textures.h"

#include <QGLContext>
#include <QGLFunctions>
#include <QtOpenGL>
#include <QDebug>
#include <QGLFramebufferObject>
#include <QtGui/QImage>


class World : public QObject, public Drawable
{
    Q_OBJECT

public:
    explicit World(QObject * parent = 0);

    void draw() override;
    void loadTextures(Texture * texture) override;
    void loadTextures(Textures * textures);
    void init();

private:

private:
    Brick *brick = new Brick();
};

#endif // WORLD_H
