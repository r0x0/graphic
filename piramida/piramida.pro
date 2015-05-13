TEMPLATE = app
QT       += console
CONFIG   -= qt

LIB += -lGL -lGLU -lglew -lglut



SOURCES += main.cpp \
    graphic/World.cpp \
    graphic/objects/Area.cpp \
    graphic/objects/Brick.cpp \
    graphic/objects/MovableObject.cpp \
    graphic/objects/Object.cpp \
    core/engine.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    graphic/World.h \
    graphic/objects/Area.h \
    graphic/objects/Brick.h \
    graphic/objects/MovableObject.h \
    graphic/objects/Object.h \
    core/engine.h

FORMS +=

