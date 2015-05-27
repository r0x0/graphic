TEMPLATE = app
QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

LIBS += -lglut


SOURCES += main.cpp \
    graphic/World.cpp \
    graphic/objects/Area.cpp \
    graphic/objects/Brick.cpp \
    core/DrawWidget.cpp \
    core/Engine.cpp \
    MainWindow.cpp \
    graphic/objects/Object.cpp

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
    core/Engine.h

FORMS += \
    mainwindow.ui

DISTFILES +=

RESOURCES += \
    resources.qrc

