#include "World.h"



World::World(int size, int piramidHeight, QObject *parent) : QThread(parent) {
    brickList = new list<Brick* >();
    areaList = new list<Area* >();
    initAreas(size);
    this->size = size;
    this->piramidHeight = piramidHeight;
    animationFinished = false;
    stop = false;
    animatedbricks = new map<Brick*, float>();
    speed =1;
    toDobricks = new list<Brick*>();
    generateToDoList();
}


World::~World(){
    for(auto area : *areaList){
        delete area;
    }
    for(auto brick : *brickList){
        delete brick;
    }
    brickList->clear();
    delete areaList;
    delete brickList;
    delete animatedbricks;
    delete toDobricks;
}

void World::run()
{
    int lastBrickCreated  = 0;

    while(!stop && !animationFinished){
        if(animatedbricks->size() < 10 && lastBrickCreated >25 && toDobricks->size() > 0){
            lastBrickCreated = 0;
            Brick *animatedbrick = getNextBrick();
            QMutexLocker l(&brickListMutex);
            brickList->push_back(animatedbrick);
            l.unlock();
            QMutexLocker l2(&animatedListMutex);
            animatedbrick->movePosition(0,100,0);
            (*animatedbricks)[animatedbrick] = 100;
        }
        setNewPosition();
        if(toDobricks->size() == 0 && animatedbricks->size()==0){
            animationFinished = true;
            emit finished();
        }
        lastBrickCreated++;
        QThread::msleep(20 / speed);
    }
}

inline Brick * World::getNextBrick(){
    Brick *ob = toDobricks->back();
    toDobricks->pop_back();
    return ob;
}

inline void World::setNewPosition(){
    QMutexLocker l2(&animatedListMutex);
    for(map<Brick*, float>::iterator it = animatedbricks->begin(); it != animatedbricks->end();){
        Brick * b = it->first;
        float value = it->second;

        if(value<10){
            value-=.05;
            b->movePosition(0,-.05,0);
        } else {
            value-=1;
            b->movePosition(0,-1,0);
        }

        if(value<=0){
            it = animatedbricks->erase(it);
            b->movePosition(0,-value,0);
        } else {
            (*animatedbricks)[b] = value;
            ++it;
        }
    }


}

void World::generateToDoList()
{
    int todo = 4;
    int height = (piramidHeight-1)*2 ;
    int shortwall = 0;
    float xpos = size/2;
    float zpos = size/2;
    float xposDif = +1;
    float zposDif = +1;

    toDobricks->push_back(new Brick(xpos, height, zpos));


    for(int i = 2; i <= piramidHeight ; i++){
        height-=2 ;

        for(int j=0; j< i; j++){
            toDobricks->push_back(new Brick(xpos -xposDif + (j)*2, height, zpos -zposDif));
            toDobricks->push_back(new Brick(xpos -xposDif + (j)*2, height, zpos +zposDif));
        }

        for(int j=1; j<= shortwall; j++){
            toDobricks->push_back(new Brick(xpos -xposDif, height, zpos -zposDif + (j)*2));
            if( i == piramidHeight && j == shortwall/2 +1){
                continue;
            }
            toDobricks->push_back(new Brick(xpos +xposDif, height, zpos -zposDif + (j)*2));
        }

        xposDif+=1;
        zposDif+=1;

        todo +=4;
        shortwall++;
    }
}

void World::draw()
{
    glBindTexture(GL_TEXTURE_2D, textures->brickTexture->texture[filter]);              // Select A Texture Based On filter
    QMutexLocker l(&brickListMutex);
    for(Brick* brick : *brickList){
        brick->draw();
    }
    l.unlock();

    glBindTexture(GL_TEXTURE_2D, textures->areaTexture->texture[filter]);              // Select A Texture Based On filter
    for(Area* area : *areaList){
        area->draw();
    }
}

void World::loadTextures(Textures2 *textures)
{
    this->textures = textures;
    glGenTextures(3, textures->brickTexture->texture);

    // texture 1 (poor quality scaling)
    glBindTexture(GL_TEXTURE_2D, textures->brickTexture->texture[0]);   // 2d texture (x and y size)
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST); // cheap scaling when image bigger than texture
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST); // cheap scaling when image smalled than texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP );
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP );
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
            glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE, GL_INTENSITY);
    // 2d texture, level of detail 0 (normal), 3 components (red, green, blue), x size from image, y size from image,
    // border 0 (normal), rgb color data, unsigned byte data, and finally the data itself.
    glTexImage2D(GL_TEXTURE_2D, 0, 3, textures->brickTexture->image->size().width(), textures->brickTexture->image->size().height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, textures->brickTexture->image->bits());

    // texture 2 (linear scaling)
    glBindTexture(GL_TEXTURE_2D, textures->brickTexture->texture[1]);   // 2d texture (x and y size)
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); // scale linearly when image bigger than texture
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); // scale linearly when image smalled than texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP );
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP );
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
            glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE, GL_INTENSITY);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, textures->brickTexture->image->size().width(), textures->brickTexture->image->size().height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, textures->brickTexture->image->bits());

    // texture 3 (mipmapped scaling)
    glBindTexture(GL_TEXTURE_2D, textures->brickTexture->texture[2]);   // 2d texture (x and y size)
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST); // scale linearly when image bigger than texture
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST); // scale linearly + mipmap when image smalled than texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP );
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP );
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
            glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE, GL_INTENSITY);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, textures->brickTexture->image->size().width(), textures->brickTexture->image->size().height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, textures->brickTexture->image->bits());



    glGenTextures(3, textures->areaTexture->texture);

    // texture 1 (poor quality scaling)
    glBindTexture(GL_TEXTURE_2D, textures->areaTexture->texture[0]);   // 2d texture (x and y size)

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST); // cheap scaling when image bigger than texture
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST); // cheap scaling when image smalled than texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP );
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP );
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
            glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE, GL_INTENSITY);
    // 2d texture, level of detail 0 (normal), 3 components (red, green, blue), x size from image, y size from image,
    // border 0 (normal), rgb color data, unsigned byte data, and finally the data itself.
    glTexImage2D(GL_TEXTURE_2D, 0, 3, textures->areaTexture->image->size().width(), textures->areaTexture->image->size().height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, textures->areaTexture->image->bits());

    // texture 2 (linear scaling)
    glBindTexture(GL_TEXTURE_2D, textures->areaTexture->texture[1]);   // 2d texture (x and y size)
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); // scale linearly when image bigger than texture
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); // scale linearly when image smalled than texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP );
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP );
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
            glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE, GL_INTENSITY);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, textures->areaTexture->image->size().width(), textures->areaTexture->image->size().height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, textures->areaTexture->image->bits());

    // texture 3 (mipmapped scaling)
    glBindTexture(GL_TEXTURE_2D, textures->areaTexture->texture[2]);   // 2d texture (x and y size)
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST); // scale linearly when image bigger than texture
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST); // scale linearly + mipmap when image smalled than texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP );
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP );
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
            glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE, GL_INTENSITY);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, textures->areaTexture->image->size().width(), textures->areaTexture->image->size().height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, textures->areaTexture->image->bits());

}

void World::setFilter(int fileter)
{
    this->filter = fileter;
}

void World::setSpeedDown()
{
    if(speed>1){
        speed--;
    }
}

void World::setSpeedUp()
{
    if(speed<4){
        speed++;
    }
}



void World::initAreas(int size){
    int size2 = -size/2;
    for(int row = size2 ; row < -size2; row++){
        for(int column = size2 ; column < -size2; column++){
            Area * a = new Area(row*2, 0, column*2);
            areaList->push_back(a);
        }
    }
}
