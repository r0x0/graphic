#include "DrawWidget.h"

#include <QDebug>
#include <math.h>

GLfloat LightAmbient[]= { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat LightDiffuse[]= { 1.0f, 1.0f, 1.0f, 0.2f };
GLfloat specularLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat lightExponent = 10;
  GLfloat lightCutoff = 40;
GLfloat LightPosition[]= { 50.0f,200.0f, 100.0f, 1.0f };
GLfloat spot_direction[] = { 0, -1.0, -0.5 };
GLfloat fogColor[4]= {0.4f, 0.4f, 0.0f, 1.0f};      // Fog Color
GLuint fogMode[]= { GL_EXP, GL_EXP2, GL_LINEAR };   // Storage For Three Types Of Fog

//GLUquadric *quadratic;               // Storage For Our Quadratic Objects ( NEW )

float points[ 45 ][ 45 ][3];                    // The Array For The Points On The Grid Of Our "Wave"
int wiggle_count = 0;                       // Counter Used To Control How Fast Flag Waves
GLfloat hold;                           // Temporarily Holds A Floating Point Value

QGLFormat desiredFormat()
{
    QGLFormat fmt;
    fmt.setSwapInterval(1);
    return fmt;
}

DrawWidget::DrawWidget(QWidget *parent) : QGLWidget(desiredFormat(), parent) {
    setMouseTracking(true);
    prepareGl();
    int piramidHeight = 9;
    int size = 200;
    zpos = 95;//size/2 - size*.1f;
    xpos = zpos;
    ypos = -10;
    lookupdown=10;

    world = new World(size, piramidHeight);
    connect(world, SIGNAL(finished()), this, SLOT(setFlag()));
    world->start();
}

void DrawWidget::prepareGl(){
    // create the framebuffer object - make sure to have a current
    // context before creating it
    makeCurrent();
    fbo = new QGLFramebufferObject(512, 512);
    timerId = startTimer(50);

    connect(updater, SIGNAL(timeout()), this, SLOT(updateGL()));
    connect(cameraUpdater, SIGNAL(timeout()), this, SLOT(updateCamera()));
    if(format().swapInterval() == -1)
        {
            // V_blank synchronization not available (tearing likely to happen)
            qDebug("Swap Buffers at v_blank not available: refresh at approx 60fps.");
            updater->setInterval(17);
        }
        else
        {
            // V_blank synchronization available
            updater->setInterval(0);
        }
    cameraUpdater->setInterval(20);
    updater->start();
    cameraUpdater->start();
    update();
}

DrawWidget::~DrawWidget()
{
    glDeleteLists(pbufferList, 1);
    delete fbo;
}

void DrawWidget::initializeGL()
{

    loadTextures();

    glEnable(GL_TEXTURE_2D);                            // Enable Texture Mapping
    glShadeModel(GL_SMOOTH);                            // Enable Smooth Shading
    glClearColor(0.0f, 0.0f, 0.1f, 0.5f);               // Black Background
    glClearDepth(1.0f);                                 // Depth Buffer Setup
    glDepthFunc(GL_LEQUAL);                             // The Type Of Depth Testing To Do
    glEnable(GL_NORMALIZE);	// automatically convert normals to unit normals
    glCullFace(GL_FRONT);

    glColor4f(1.0f,1.0f,1.0f,0.5f);         // Full Brightness, 50% Alpha ( NEW )
    glBlendFunc(GL_SRC_ALPHA,GL_DONT_CARE);       // Blending Function For Translucency Based On Source Alpha Value ( NEW )

    glMatrixMode(GL_PROJECTION);
     glLoadIdentity();				// Reset The Projection Matrix

    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Really Nice Perspective

    glMatrixMode(GL_MODELVIEW);

    glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);             // Setup The Ambient Light
    glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);             // Setup The Diffuse Light
    glLightfv(GL_LIGHT1, GL_SPECULAR, specularLight);
    glLightfv(GL_LIGHT1, GL_POSITION,LightPosition);            // Position The Light
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);
//    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, lightCutoff);
//    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, lightExponent);
//    glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.1);

    glEnable(GL_LIGHT1);                            // Enable Light One

//    glLightModeli(GL_LIGHT_MODEL_SPECULAR_VECTOR_APPLE, GL_TRUE);
    glEnable(GL_LIGHTING);

    // Set material properties.
//               float rgba[3] = {0.3, 0.5, 1};
//               glMaterialfv(GL_FRONT, GL_AMBIENT, rgba);
//               glMaterialfv(GL_FRONT, GL_SPECULAR, rgba);
//               glMaterialf(GL_FRONT, GL_SHININESS, 0.5f);

    glEnable(GL_DEPTH_TEST);                            // Enables Depth Testing

//    FOG
    glClearColor(0.38f,0.8f,1,1.0f);          // We'll Clear To The Color Of The Fog ( Modified )

    glFogi(GL_FOG_MODE, fogMode[fogfilter]);        // Fog Mode
    glFogfv(GL_FOG_COLOR, fogColor);            // Set Fog Color
    glFogf(GL_FOG_DENSITY, 0.1f);              // How Dense Will The Fog Be
    glHint(GL_FOG_HINT, GL_NICEST);          // Fog Hint Value
    glFogf(GL_FOG_START, 0.5f);             // Fog Start Depth
    glFogf(GL_FOG_END, 1.0f);               // Fog End Depth
//    glEnable(GL_FOG);                   // Enables GL_FOG

//    quadratic=gluNewQuadric();          // Create A Pointer To The Quadric Object ( NEW )
//    gluQuadricNormals(quadratic, GLU_SMOOTH);   // Create Smooth Normals ( NEW )
//    gluQuadricTexture(quadratic, GL_TRUE);      // Create Texture Coords ( NEW )

    glPolygonMode( GL_BACK, GL_FILL );          // Back Face Is Filled In
    glPolygonMode( GL_FRONT, GL_LINE );         // Front Face Is Drawn With Lines

    // Loop Through The X Plane
    for(int x=0; x<45; x++)
    {
        // Loop Through The Y Plane
        for(int y=0; y<45; y++)
        {
            // Apply The Wave To Our Mesh
            points[x][y][0]=float((x/5.0f)-4.5f);
            points[x][y][1]=float((y/5.0f)-4.5f);
            points[x][y][2]=float(sin((((x/5.0f)*40.0f)/360.0f)*3.141592654*2.0f));
        }
    }

    update();
}

void DrawWidget::resizeGL(int w, int h)
{
    if (h==0){				// Prevent A Divide By Zero If The Window Is Too Small
        h=1;
    }

    glViewport(0, 0, w, h);		// Reset The Current Viewport And Perspective Transformation

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-zoom, zoom, -zoom, zoom, -15.0, 15.0);

    glMatrixMode(GL_MODELVIEW);
}

void DrawWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(cameraAuto) return;
    changeView(event->pos());
}

void DrawWidget::changeView(QPoint pos){
    float change = lastPos.y() - pos.y();
    if(zoom<10 || zoom >-10){
        change = change * .1f;
    }
    z -= change;
    lookupdown -= change;
    yrot+= lastPos.x() - pos.x();
    lastPos = pos;
}

void DrawWidget::wheelEvent(QWheelEvent *event)
{
    if(cameraAuto) return;
    float change = -(event->delta()/120);
    if(zoom<10 || zoom>-10){
        change *= 0.1f;
    }
    zoomView(change);
}

void DrawWidget::updateCamera()
{
    if(!cameraAuto) return;

    cameraCount++;

    yrot++;

    if(cameraCount==1000){
        zoomValue = -0.02;
    }
    else if(cameraCount==2000){
        zoomValue = -0.01;
    }
    if(cameraCount < 2500){
        zoomView(zoomValue);
            lookupdown+=zoomValue;
            ypos-=zoomValue;
            zpos+=0.01;
            xpos+=0.01;
    }
//        if(cameraCount%20 == 0){
//            lookupdown--;
////            ypos--;
//            xpos+=.2;
//                    zpos+=.2;
//        }
//    }

//        zoomView(zoomValue);

//    if(cameraCount<30){
////        xpos+=.2;
////        zpos+=.2;
//        ypos-=.2;
//    } else if(cameraCount <100){
////        xpos-=.2;
////        zpos-=.2;
//    }

}

void DrawWidget::zoomView(float change){
    zoom += change;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-zoom, zoom, -zoom, zoom, -70.0, 70.0);

    glMatrixMode(GL_MODELVIEW);
}

void DrawWidget::paintGL()
{

    // calculate translations and rotations.
    float xtrans = -xpos;
    float ztrans = -zpos;
    GLfloat ytrans = ypos;//-walkbias-0.25f;
    float sceneroty = 360.0f - yrot;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );		// Clear The Screen And The Depth Buffer
    glLoadIdentity();
//    glPushMatrix ();
//    turnOnOffLight();


    glPushMatrix();
        glPolygonMode( GL_FRONT, GL_FILL );          // Back Face Is Filled In
        glPolygonMode( GL_BACK, GL_NONE );         // Front Face Is Drawn With Lines
        glRotatef(lookupdown, 1.0f, 0, 0);
        glRotatef(sceneroty, 0, 1.0f, 0);
        glTranslatef(xtrans, ytrans, ztrans);
        glLightfv (GL_LIGHT0, GL_POSITION, LightPosition);
        glEnable(GL_TEXTURE_2D);
        world->draw();
    glPopMatrix();
    glPushMatrix();
        glPolygonMode( GL_BACK, GL_FILL );          // Back Face Is Filled In
        glPolygonMode( GL_FRONT, GL_LINE );         // Front Face Is Drawn With Lines
        glRotatef(lookupdown, 1.0f, 0, 0);
        glRotatef(sceneroty, 0, 1.0f, 0);
        glTranslatef(xtrans, ytrans, ztrans);
        drawFlag();
    glPopMatrix();

//    glPushMatrix();
//        glDisable(GL_TEXTURE_2D);
//        turnOnOffLight();
//        glRotatef(lookupdown, 1.0f, 0, 0);
//        glRotatef(sceneroty, 0, 1.0f, 0);
//        glTranslatef(xtrans, ytrans, ztrans);
//        float lpos[] = {LightPosition[0],LightPosition[1],LightPosition[2],LightPosition[3]};
//        glLightfv (GL_LIGHT0, GL_POSITION, lpos);
//        turnOnOffLight();
//    glPopMatrix();

    swapBuffers();
}

inline void DrawWidget::drawFlag(){
    if(!shouldDrawFlag) return;


    int x, y;                       // Loop Variables
    float float_x, float_y, float_xb, float_yb;     // Used To Break The Flag Into Tiny Quads
    glBindTexture(GL_TEXTURE_2D, textures->flagTexture->texture[filter]);       // Select Our Texture

    glTranslatef(102, 20, 100);
glScalef(.5,.5,.5);

    glBegin(GL_QUADS);                  // Start Drawing Our Quads
    for( x = 0; x < 44; x++ )                // Loop Through The X Plane (44 Points)
    {
        for( y = 0; y < 44; y++ )            // Loop Through The Y Plane (44 Points)
        {
            float_x = float(x)/44.0f;       // Create A Floating Point X Value
            float_y = float(y)/44.0f;       // Create A Floating Point Y Value
            float_xb = float(x+1)/44.0f;        // Create A Floating Point Y Value+0.0227f
            float_yb = float(y+1)/44.0f;        // Create A Floating Point Y Value+0.0227f
            glTexCoord2f( float_x, float_y);    // First Texture Coordinate (Bottom Left)
            glVertex3f( points[x][y][0], points[x][y][1], points[x][y][2] );

            glTexCoord2f( float_x, float_yb );  // Second Texture Coordinate (Top Left)
            glVertex3f( points[x][y+1][0], points[x][y+1][1], points[x][y+1][2] );

            glTexCoord2f( float_xb, float_yb ); // Third Texture Coordinate (Top Right)
            glVertex3f( points[x+1][y+1][0], points[x+1][y+1][1], points[x+1][y+1][2] );

            glTexCoord2f( float_xb, float_y );  // Fourth Texture Coordinate (Bottom Right)
            glVertex3f( points[x+1][y][0], points[x+1][y][1], points[x+1][y][2] );
        }
    }
    glEnd();                        // Done Drawing Our Quads

    if( wiggle_count == 2 )                 // Used To Slow Down The Wave (Every 2nd Frame Only)
    {
    for( y = 0; y < 45; y++ )            // Loop Through The Y Plane
        {
            hold=points[0][y][2];           // Store Current Value One Left Side Of Wave
            for( x = 0; x < 44; x++)     // Loop Through The X Plane
            {
                // Current Wave Value Equals Value To The Right
                points[x][y][2] = points[x+1][y][2];
            }
            points[44][y][2]=hold;          // Last Value Becomes The Far Left Stored Value
        }
        wiggle_count = 0;               // Set Counter Back To Zero
    }
    wiggle_count++;                     // Increase The Counter
}

void DrawWidget::loadTextures(){
    qDebug() << "Textures loading...";
    textures = new Textures2();

    Texture * brick = new Texture();
    QImage brickIm = QGLWidget::convertToGLFormat( QImage(":/res/graphic/textures/cube.jpg") );
    brick->image = new QImage(brickIm.scaled(512,512,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
    textures->brickTexture = brick;


    Texture * area = new Texture();
    QImage areaIm = QGLWidget::convertToGLFormat( QImage(":/res/graphic/textures/sand.png") );
    area->image = new QImage(areaIm.scaled(512,512,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
    textures->areaTexture = area;

    Texture * flag = new Texture();
    QImage flagIm = QGLWidget::convertToGLFormat( QImage(":/res/graphic/textures/ra.png") );
    flag->image = new QImage(flagIm.scaled(512,1024,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
    textures->flagTexture = flag;

    glGenTextures(3, textures->brickTexture->texture);

    // texture 1 (poor quality scaling)
    glBindTexture(GL_TEXTURE_2D, textures->flagTexture->texture[0]);   // 2d texture (x and y size)
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST); // cheap scaling when image bigger than texture
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST); // cheap scaling when image smalled than texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP );
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP );
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
            glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE, GL_INTENSITY);
    // 2d texture, level of detail 0 (normal), 3 components (red, green, blue), x size from image, y size from image,
    // border 0 (normal), rgb color data, unsigned byte data, and finally the data itself.
    glTexImage2D(GL_TEXTURE_2D, 0, 3, textures->flagTexture->image->size().width(), textures->flagTexture->image->size().height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, textures->flagTexture->image->bits());


    world->loadTextures(textures);


//    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, textures->areaTexture->texture, 0);
}

void DrawWidget::blender(){
    blend = !blend;
    if(blend)
    {
        qDebug() << "Enable blender";
        glEnable(GL_BLEND);     // Turn Blending On
        glDisable(GL_DEPTH_TEST);   // Turn Depth Testing Off
    }
    else                    // Otherwise
    {
        qDebug() << "Disable blender";
        glDisable(GL_BLEND);        // Turn Blending Off
        glEnable(GL_DEPTH_TEST);    // Turn Depth Testing On
    }
}

void DrawWidget::turnOnOffLight()
{
    light = ! light;
    if (!light)             // If Not Light
    {
        qDebug() << "disable light";
        glDisable(GL_LIGHTING);     // Disable Lighting
    }
    else                    // Otherwise
    {
        qDebug() << "Enable light";
        glEnable(GL_LIGHTING);      // Enable Lighting
    }
}

void DrawWidget::moveUp()
{
    xpos -= (float)sin(yrot*piover180) * 0.5f;
    zpos -= (float)cos(yrot*piover180) * 0.5f;
    if (walkbiasangle >= 359.0f)
        walkbiasangle = 0.0f;
    else
        walkbiasangle+= 10;
    walkbias = (float)sin(walkbiasangle * piover180)/20.0f;
}

void DrawWidget::moveBack()
{
    xpos += (float)sin(yrot*piover180) * 0.5f;
    zpos += (float)cos(yrot*piover180) * 0.5f;
    if (walkbiasangle <= 1.0f)
        walkbiasangle = 359.0f;
    else
        walkbiasangle-= 10;
    walkbias = (float)sin(walkbiasangle * piover180)/20.0f;
}

void DrawWidget::moveRight()
{
}

void DrawWidget::moveLeft()
{
}

void DrawWidget::setFilter(int filter){
    this->filter = filter;
    world->setFilter(filter);
}

void DrawWidget::setFog(){
    this->fog = !fog;
    if(fog){
        glEnable(GL_FOG);
    } else {
        glDisable(GL_FOG);
    }
}

void DrawWidget::changeFogMode(){
    if(!fog) return;
    fogfilter+=1;                   // Increase fogfilter By One
    if (fogfilter>2)             // Is fogfilter Greater Than 2?
    {
        fogfilter=0;                // If So, Set fogfilter To Zero
    }
    glFogi (GL_FOG_MODE, fogMode[fogfilter]);   // Fog Mode
}

void DrawWidget::chnageCamera(bool camera)
{
    cameraAuto = camera;
}

// degrees to radians...2 PI radians = 360 degrees
float DrawWidget::rad(float angle)
{
    return angle * piover180;
}

void DrawWidget::speedDown(){
    world->setSpeedDown();
}


void DrawWidget::speedUp(){
    world->setSpeedUp();
}

void DrawWidget::setFlag()
{
    qDebug() << "SET FLAG";
    shouldDrawFlag = true;
}
