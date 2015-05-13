#include "window.h"

MainWindow::MainWindow()
{
    display = XOpenDisplay(NULL);

     if(display == NULL) {
            printf("\n\tcannot connect to X server\n\n");
            exit(1);
     }

     rootWindow = DefaultRootWindow(display);

     visualInfo = glXChooseVisual(display, 0, initAttr);

     if(visualInfo == NULL) {
            printf("\n\tno appropriate visual found\n\n");
            exit(2);
     }
     else {
            printf("\n\tvisual %p selected\n", (void *)visualInfo->visualid); /* %p creates hexadecimal output like in glxinfo */
     }


     colorMap = XCreateColormap(display, rootWindow, visualInfo->visual, AllocNone);

     swa.colormap = colorMap;
     swa.event_mask = ExposureMask | KeyPressMask;

     window = XCreateWindow(display, rootWindow, 0, 0, 600, 600, 0, visualInfo->depth, InputOutput, visualInfo->visual, CWColormap | CWEventMask, &swa);

     XMapWindow(display, window);
     XStoreName(display, window, "VERY SIMPLE APPLICATION");

     glcontext = glXCreateContext(display, visualInfo, NULL, GL_TRUE);
     glXMakeCurrent(display, window, glcontext);

     glEnable(GL_DEPTH_TEST);
}

MainWindow::~MainWindow()
{

}

