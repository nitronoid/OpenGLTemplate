TEMPLATE = app
TARGET = Project

UI_HEADERS_DIR = ui
UI_DIR = ui
OBJECTS_DIR = obj
MOC_DIR = moc

QT += opengl core gui
CONFIG += console c++17
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

ASSIMPINCDIR = /public/devel/2018/include
ASSIMPLIBDIR = /public/devel/2018/lib

INCLUDEPATH += \
    /usr/local/include/glm/glm \
    /usr/local/include/glm \
    /usr/local/include/glm \
    /public/devel/2018/include/glm \
    $${ASSIMPINCDIR} \
    $$PWD/include \
    $$PWD/ui \
    $$PWD/shaders

DEPPATH = $$PWD/dep
DEPS = $$system(ls $${DEPPATH})
for(d, DEPS):INCLUDEPATH += $${DEPPATH}/$${d}/include

HEADERS += $$files(include/*.h, true)
SOURCES += $$files(src/*.cpp, true)

OTHER_FILES += \
    $$files(shaderPrograms/*, true) \
    $$files(models/*, true)

FORMS += ui/mainwindow.ui

linux:{
    LIBS += -lGL -lGLU -lGLEW -L$${ASSIMPLIBDIR} -lassimp
}


DEFINES += GLM_ENABLE_EXPERIMENTAL GLM_FORCE_CTOR_INIT
DISTFILES += $$files(shaders/*, true)

QMAKE_CXXFLAGS += -std=c++17 -Ofast -msse -msse2 -msse3 -march=native -fopenmp -frename-registers -funroll-loops 
QMAKE_CXXFLAGS += -Wall -Wextra -pedantic-errors

QMAKE_LFLAGS += -fopenmp


