#include "World.h"



World::World(QObject *parent) : QObject(parent) {

    init();
}

void World::init(){

}


void World::draw()
{
    brick->draw();
}

void World::loadTextures(Texture *texture)
{
    // nothing here
}

void World::loadTextures(Textures *textures)
{
    brick->loadTextures(textures->brickTexture);
}
