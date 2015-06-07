TEMPLATE = app
QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

LIBS += -lglut
QMAKE_CFLAGS += -std=c++11
QMAKE_CXXFLAGS += -std=c++11


SOURCES += main.cpp \
    graphic/World.cpp \
    graphic/objects/Area.cpp \
    graphic/objects/Brick.cpp \
    core/DrawWidget.cpp \
    MainWindow.cpp \
    graphic/objects/Object.cpp \
    graphic/objects/Textures.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    graphic/World.h \
    graphic/objects/Area.h \
    graphic/objects/Brick.h \
    graphic/objects/Object.h \
    graphic/objects/Drawable.h \
    MainWindow.h \
    core/DrawWidget.h \
    graphic/objects/Texture.h \
    graphic/objects/Textures.h

FORMS += \
    mainwindow.ui

DISTFILES +=

RESOURCES += \
    resources.qrc

