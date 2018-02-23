#-------------------------------------------------
#
# Project created by QtCreator 2018-01-09T14:02:30
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

LIBS += -L$$PWD/3rd_party/cork/lib/ -lwincork
LIBS    += -lopengl32 -lglu32
TARGET = stl_editor
TEMPLATE = app
#DEFINES += _USE_MATH_DEFINES

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
    utils.cpp \
    stlfile.cpp \
    cell.cpp \
    cube.cpp \
    pyramid.cpp \
    icosphere.cpp \
    customcell.cpp \
    rotatedialog.cpp \
    stlpreview.cpp \
    importdialog.cpp

HEADERS += \
        mainwindow.h \
    triangle.h \
    vertex.h \
    utils.h \
    stlfile.h \
    cell.h \
    cube.h \
    pyramid.h \
    icosphere.h \
    customcell.h \
    rotatedialog.h \
    stlpreview.h \
    ui_mainwindow.h \
    3rd_party/cork/accel/aabvh.h \
    3rd_party/cork/file_formats/files.h \
    3rd_party/cork/isct/absext4.h \
    3rd_party/cork/isct/empty3d.h \
    3rd_party/cork/isct/ext4.h \
    3rd_party/cork/isct/fixext4.h \
    3rd_party/cork/isct/fixint.h \
    3rd_party/cork/isct/gmpext4.h \
    3rd_party/cork/isct/quantization.h \
    3rd_party/cork/isct/triangle.h \
    3rd_party/cork/isct/unsafeRayTriIsct.h \
    3rd_party/cork/math/bbox.h \
    3rd_party/cork/math/ray.h \
    3rd_party/cork/math/vec.h \
    3rd_party/cork/mesh/mesh.decl.h \
    3rd_party/cork/mesh/mesh.h \
    3rd_party/cork/rawmesh/rawMesh.h \
    3rd_party/cork/util/iterPool.h \
    3rd_party/cork/util/memPool.h \
    3rd_party/cork/util/prelude.h \
    3rd_party/cork/util/shortVec.h \
    3rd_party/cork/util/unionFind.h \
    3rd_party/cork/cork.h \
    importdialog.h


FORMS += \
        mainwindow.ui

#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../dev/mpir-3.0.0/lib/Win32/release/ -lmpir
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../dev/mpir-3.0.0/lib/Win32/debug/ -lmpir

#INCLUDEPATH += $$PWD/../../../../dev/mpir-3.0.0/lib/Win32/Release
#DEPENDPATH += $$PWD/../../../../dev/mpir-3.0.0/lib/Win32/Release




#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../dev/mpir-3.0.0/lib/Win32/release/ -lmpir
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../dev/mpir-3.0.0/lib/Win32/debug/ -lmpir

#INCLUDEPATH += $$PWD/../../../../dev/mpir-3.0.0/lib/Win32/Release
#DEPENDPATH += $$PWD/../../../../dev/mpir-3.0.0/lib/Win32/Release
