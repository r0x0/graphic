#include "Brick.h"

Brick::Brick() : Object(1,1,1) {
}

Brick::Brick(float x, float y, float z) : Object(x, y, z){
}

void Brick::draw()
{
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
