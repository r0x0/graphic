TEMPLATE = app
QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets



SOURCES += main.cpp \
    graphic/World.cpp \
    graphic/objects/Area.cpp \
    graphic/objects/Brick.cpp \
    graphic/objects/MovableObject.cpp \
    graphic/objects/Object.cpp \
    core/engine.cpp \
    mainwindow.cpp \
    core/drawwidget.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    graphic/World.h \
    graphic/objects/Area.h \
    graphic/objects/Brick.h \
    graphic/objects/MovableObject.h \
    graphic/objects/Object.h \
    core/engine.h \
    mainwindow.h \
    core/drawwidget.h

FORMS += \
    mainwindow.ui

DISTFILES +=

RESOURCES += \
    resources.qrc

