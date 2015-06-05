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
#include <QThread>
#include <QMutex>
#include <QMutexLocker>

#include <list>


using namespace std;

class World : public QThread
{
    Q_OBJECT

public:
    explicit World(int size, int piramidHeight, QObject * parent = 0);

    void draw() ;
    void loadTextures(Textures * textures);
    void setFilter(int fileter);
    void setSpeedDown();
    void setSpeedUp();

    ~World();
protected:
    void run();

private:
    Textures *textures;
    int filter = 0;
    list<Area* > *areaList;
    list<Brick* > *brickList;
    QMutex brickListMutex;
    map<Brick*, float> *animatedbricks;
    list<Brick*> *toDobricks;
    QMutex animatedListMutex;
    void initAreas(int size);
    volatile int speed;
    volatile int size;
    volatile int piramidHeight;
    volatile bool stop;
    volatile bool animationFinished;

    Brick *getNextBrick();
    void setNewPosition();
    void generateToDoList();

signals:
    void finished();
};

#endif // WORLD_H
