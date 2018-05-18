TEMPLATE = app
CONFIG += console c++1z
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp

LIBS += -lpthread

HEADERS += \
    HandMadeFlyweigth.hpp \
    BoostFlyweight.hpp \
    TextFormatting.hpp
