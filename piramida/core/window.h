#ifndef WINDOW_H
#define WINDOW_H

#include<stdio.h>
#include<stdlib.h>
#include<X11/X.h>
#include<X11/Xlib.h>
#include<GL/gl.h>
#include<GL/glx.h>
#include<GL/glu.h>

using namespace std;

class MainWindow
{
public:
    MainWindow();
    ~MainWindow();

private:

    Display                 *display;
    Window                  rootWindow;
    GLint                   initAttr[5] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
    XVisualInfo             *visualInfo;
    Colormap                colorMap;
    XSetWindowAttributes    swa;
    GLXContext              glcontext;
    XWindowAttributes       gwa;
    XEvent                  xeve;
    Window                  window;
};

#endif // WINDOW_H
