#-------------------------------------------------
#
# Project created by QtCreator 2018-01-09T14:02:30
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

LIBS    += -lopengl32 -lglu32
TARGET = stl_editor
TEMPLATE = app


# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    triangle.cpp \
    vertex.cpp \
    stlpreview.cpp \
    utils.cpp \
    stlfile.cpp \
    cell.cpp \
    cube.cpp \
    pyramid.cpp \
    icosphere.cpp \
    customcell.cpp \
    rotatedialog.cpp

HEADERS += \
        mainwindow.h \
    triangle.h \
    vertex.h \
    stlpreview.h \
    utils.h \
    stlfile.h \
    cell.h \
    cube.h \
    pyramid.h \
    icosphere.h \
    customcell.h \
    rotatedialog.h

FORMS += \
        mainwindow.ui
