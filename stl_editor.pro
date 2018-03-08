#-------------------------------------------------
#
# Project created by QtCreator 2018-01-09T14:02:30
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#LIBS += -L$$PWD/3rd_party/cork/lib/ -lwincork
INCLUDEPATH += C:/dev/libigl/include
INCLUDEPATH += C:/dev/eigen
INCLUDEPATH += $$PWD/3rd_party/cork
INCLUDEPATH += C:/dev/mpir-3.0.0
LIBS    += -lopengl32 -lglu32
TARGET = stl_editor
TEMPLATE = app

QMAKE_CXXFLAGS += -bigobj

CONFIG += c++11

#INCLUDEPATH += $$PWD/../../../../dev/mpir-3.0.0/lib/Win32/Release
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
    importdialog.cpp \
    3rd_party/tinyexpr/tinyexpr.c

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
    importdialog.h \
    3rd_party/tinyexpr/tinyexpr.h


FORMS += \
        mainwindow.ui

win32: LIBS += -L$$PWD/../../../../dev/CGAL-4.10.2/build/lib/ -lCGAL-vc140-mt-gd-4.10.2

INCLUDEPATH += $$PWD/../../../../dev/CGAL-4.10.2/build/include
DEPENDPATH += $$PWD/../../../../dev/CGAL-4.10.2/build/include

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../../../../dev/CGAL-4.10.2/build/lib/CGAL-vc140-mt-gd-4.10.2.lib
else:win32-g++: PRE_TARGETDEPS += $$PWD/../../../../dev/CGAL-4.10.2/build/lib/libCGAL-vc140-mt-gd-4.10.2.a


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../dev/mpir/dll/x64/release/ -lmpir
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../dev/mpir/dll/x64/debug/ -lmpir

INCLUDEPATH += $$PWD/../../../../dev/mpir/dll/x64/Debug
DEPENDPATH += $$PWD/../../../../dev/mpir/dll/x64/Debug

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../dev/mpfr/dll/x64/release/ -lmpfr
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../dev/mpfr/dll/x64/debug/ -lmpfr

INCLUDEPATH += $$PWD/../../../../dev/mpfr/dll/x64/Debug
DEPENDPATH += $$PWD/../../../../dev/mpfr/dll/x64/Debug

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../dev/cork/win/dll/x64/release/ -lwincork
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../dev/cork/win/dll/x64/debug/ -lwincork

INCLUDEPATH += $$PWD/../../../../dev/cork/win/dll/x64/Release
DEPENDPATH += $$PWD/../../../../dev/cork/win/dll/x64/Release
