#-------------------------------------------------
#
# Project created by QtCreator 2011-05-01T10:34:43
#
#-------------------------------------------------

QT       += core gui opengl

TARGET = Hello_GLSL
TEMPLATE = app
LIBS += -lGLU -lX11


SOURCES += main.cpp\
        mainwindow.cpp \
    glrenderthread.cpp \
    glframe.cpp

HEADERS  += mainwindow.h \
    glframe.h \
    glrenderthread.h

FORMS    += mainwindow.ui
