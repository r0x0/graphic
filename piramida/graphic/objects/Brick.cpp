#include "Brick.h"

Brick::Brick() : Object(1,1,1) {
}

Brick::Brick(float x, float y, float z) : Object(x, y, z){
}

void Brick::movePosition(float x, float y, float z){
    QMutexLocker l(&mutexObj);
    this->x += x;
    this->y += y;
    this->z += z;
}

void Brick::draw()
{

//    GLfloat normal[3];

//        GLfloat materialAmbDiff[] = {0.9f, 0.5f, 0.3f, 1.0f}; // create an array of RGBA values


//        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialAmbDiff); // set the diffuse & ambient reflection colour for the front of faces

//        GLfloat materialSpecular[] = {1.0f, 1.0f, 1.0f, 1.0f}; // create an array of RGBA values (White)
//        GLfloat materialShininess[] = {60.0f}; // select value between 0-128, 128=shiniest


//        glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular); // set the colour of specular reflection
//        glMaterialfv(GL_FRONT, GL_SHININESS, materialShininess); // set shininess of the material
    QMutexLocker l(&mutexObj);

    glBegin(GL_QUADS);                          // Start Drawing Quads
    // Front Face
    glNormal3f( 0.0f, 0.0f, 1.0f);                  // Normal Pointing Towards Viewer
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f+x, -1.0f+y,  1.0f+z);  // Point 1 (Front)
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f+x, -1.0f+y,  1.0f+z);  // Point 2 (Front)
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f+x,  1.0f+y,  1.0f+z);  // Point 3 (Front)
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f+x,  1.0f+y,  1.0f+z);  // Point 4 (Front)
    // Back Face
    glNormal3f( 0.0f, 0.0f,-1.0f);                  // Normal Pointing Away From Viewer
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f+x, -1.0f+y, -1.0f+z);  // Point 1 (Back)
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f+x,  1.0f+y, -1.0f+z);  // Point 2 (Back)
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f+x,  1.0f+y, -1.0f+z);  // Point 3 (Back)
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f+x, -1.0f+y, -1.0f+z);  // Point 4 (Back)
    // Top Face
    glNormal3f( 0.0f, 1.0f, 0.0f);                  // Normal Pointing Up
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f+x,  1.0f+y, -1.0f+z);  // Point 1 (Top)
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f+x,  1.0f+y,  1.0f+z);  // Point 2 (Top)
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f+x,  1.0f+y,  1.0f+z);  // Point 3 (Top)
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f+x,  1.0f+y, -1.0f+z);  // Point 4 (Top)
    // Bottom Face
    glNormal3f( 0.0f,-1.0f, 0.0f);                  // Normal Pointing Down
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f+x, -1.0f+y, -1.0f+z);  // Point 1 (Bottom)
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f+x, -1.0f+y, -1.0f+z);  // Point 2 (Bottom)
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f+x, -1.0f+y,  1.0f+z);  // Point 3 (Bottom)
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f+x, -1.0f+y,  1.0f+z);  // Point 4 (Bottom)
    // Right face
    glNormal3f( 1.0f, 0.0f, 0.0f);                  // Normal Pointing Right
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f+x, -1.0f+y, -1.0f+z);  // Point 1 (Right)
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f+x,  1.0f+y, -1.0f+z);  // Point 2 (Right)
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f+x,  1.0f+y,  1.0f+z);  // Point 3 (Right)
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f+x, -1.0f+y,  1.0f+z);  // Point 4 (Right)
    // Left Face
    glNormal3f(-1.0f, 0.0f, 0.0f);                  // Normal Pointing Left
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f+x, -1.0f+y, -1.0f+z);  // Point 1 (Left)
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f+x, -1.0f+y,  1.0f+z);  // Point 2 (Left)
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f+x,  1.0f+y,  1.0f+z);  // Point 3 (Left)
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f+x,  1.0f+y, -1.0f+z);  // Point 4 (Left)
    glEnd();                                // Done Drawing Quads
}

