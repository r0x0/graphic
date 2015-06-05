#include "Area.h"

Area::Area() : Object(1,1,1) {
}

Area::Area(float x, float y, float z) : Object(x, y, z){
}
void Area::draw()
{
    glBegin(GL_QUADS);                          // Start Drawing Quads
    glNormal3f( 0+x/100, 5+y/100, 0+z/100);                  // Normal Pointing Up
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f+x, -1.0f+y, -1.0f+z);  // Point 1 (Bottom)
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f+x, -1.0f+y, -1.0f+z);  // Point 2 (Bottom)
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f+x, -1.0f+y,  1.0f+z);  // Point 3 (Bottom)
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f+x, -1.0f+y,  1.0f+z);  // Point 4 (Bottom)
    glEnd();
}
