TEMPLATE = app
CONFIG += console c++1z
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lGL -lGLU -lglut

SOURCES += \
        main.cpp

HEADERS += \
    BitmapTest.hpp
