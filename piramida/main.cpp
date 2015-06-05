#include "MainWindow.h"

#include <QApplication>
#include <QGLWidget>

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);

    MainWindow window;
    window.resize(1024,800);
    window.show();

    return app.exec();
}
