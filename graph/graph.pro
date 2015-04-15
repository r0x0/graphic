#-------------------------------------------------
#
# Project created by QtCreator 2015-03-21T13:28:50
#
#-------------------------------------------------

QT       += core gui opengl
LIBS = -lglut -lGLU


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = graph
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    graphic/objects/Brick.cpp \
    graphic/objects/Area.cpp \
    graphic/objects/MovableObject.cpp \
    graphic/objects/Object.cpp \
    graphic/World.cpp \
    GraphicWidget.cpp

HEADERS  += mainwindow.h \
    includeGL.h \
    graphic/objects/Brick.h \
    graphic/objects/Area.h \
    graphic/objects/MovableObject.h \
    graphic/objects/Object.h \
    graphic/World.h \
    GraphicWidget.h

FORMS    += mainwindow.ui
