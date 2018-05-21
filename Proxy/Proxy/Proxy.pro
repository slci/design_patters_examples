TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -stdlib=libc++

LIBS += -lc++abi

SOURCES += \
        main.cpp
