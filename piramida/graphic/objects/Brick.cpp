#include "Brick.h"

Brick::Brick() : Object(1,1,1) {
}

Brick::Brick(float x, float y, float z) : Object(x, y, z){
}

void Brick::draw()
{


    glBindTexture(GL_TEXTURE_2D, texture[0]);              // Select A Texture Based On filter

    glBegin(GL_QUADS);                          // Start Drawing Quads
    // Front Face
    glNormal3f( 0.0f, 0.0f, 1.0f);                  // Normal Pointing Towards Viewer
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);  // Point 1 (Front)
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);  // Point 2 (Front)
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);  // Point 3 (Front)
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);  // Point 4 (Front)
    // Back Face
    glNormal3f( 0.0f, 0.0f,-1.0f);                  // Normal Pointing Away From Viewer
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);  // Point 1 (Back)
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);  // Point 2 (Back)
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);  // Point 3 (Back)
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);  // Point 4 (Back)
    // Top Face
    glNormal3f( 0.0f, 1.0f, 0.0f);                  // Normal Pointing Up
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);  // Point 1 (Top)
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);  // Point 2 (Top)
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);  // Point 3 (Top)
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);  // Point 4 (Top)
    // Bottom Face
    glNormal3f( 0.0f,-1.0f, 0.0f);                  // Normal Pointing Down
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);  // Point 1 (Bottom)
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);  // Point 2 (Bottom)
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);  // Point 3 (Bottom)
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);  // Point 4 (Bottom)
    // Right face
    glNormal3f( 1.0f, 0.0f, 0.0f);                  // Normal Pointing Right
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);  // Point 1 (Right)
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);  // Point 2 (Right)
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);  // Point 3 (Right)
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);  // Point 4 (Right)
    // Left Face
    glNormal3f(-1.0f, 0.0f, 0.0f);                  // Normal Pointing Left
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);  // Point 1 (Left)
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);  // Point 2 (Left)
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);  // Point 3 (Left)
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);  // Point 4 (Left)
    glEnd();                                // Done Drawing Quads
}

void Brick::loadTextures(Texture *texture)
{

//    glGenTextures(3, this->texture);

//    // Create Nearest Filtered Texture
//    glBindTexture(GL_TEXTURE_2D, this->texture[0]);
//    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST); // ( NEW )
//    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST); // ( NEW )
//    glTexImage2D(GL_TEXTURE_2D, 0, 3, texture->image->size().width(), texture->image->size().width(), 0, GL_RGB, GL_UNSIGNED_BYTE, texture->image->bits());

//    // Create Linear Filtered Texture
//    glBindTexture(GL_TEXTURE_2D, this->texture[1]);
//    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
//    glTexImage2D(GL_TEXTURE_2D, 0, 3, texture->image->size().width(), texture->image->size().width(), 0, GL_RGB, GL_UNSIGNED_BYTE, texture->image->bits());

//    // Create MipMapped Texture
//    glBindTexture(GL_TEXTURE_2D, this->texture[2]);
//    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST); // ( NEW )
//    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, texture->image->size().width(), texture->image->size().width(), GL_RGB, GL_UNSIGNED_BYTE, texture->image->bits()); // ( NEW )

    // Create Textures
        glGenTextures(3, &(this->texture[0]));

        // texture 1 (poor quality scaling)
        glBindTexture(GL_TEXTURE_2D, this->texture[0]);   // 2d texture (x and y size)

        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST); // cheap scaling when image bigger than texture
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST); // cheap scaling when image smalled than texture

        // 2d texture, level of detail 0 (normal), 3 components (red, green, blue), x size from image, y size from image,
        // border 0 (normal), rgb color data, unsigned byte data, and finally the data itself.
        glTexImage2D(GL_TEXTURE_2D, 0, 3, texture->image->size().width(), texture->image->size().height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, texture->image->bits());

        // texture 2 (linear scaling)
        glBindTexture(GL_TEXTURE_2D, this->texture[1]);   // 2d texture (x and y size)
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); // scale linearly when image bigger than texture
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); // scale linearly when image smalled than texture
        glTexImage2D(GL_TEXTURE_2D, 0, 3, texture->image->size().width(), texture->image->size().height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, texture->image->bits());

        // texture 3 (mipmapped scaling)
        glBindTexture(GL_TEXTURE_2D, this->texture[2]);   // 2d texture (x and y size)
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); // scale linearly when image bigger than texture
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST); // scale linearly + mipmap when image smalled than texture
        glTexImage2D(GL_TEXTURE_2D, 0, 3, texture->image->size().width(), texture->image->size().height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, texture->image->bits());

}
