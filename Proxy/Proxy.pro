TEMPLATE = app
CONFIG += console c++1z
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += /usr/include/c++/v1

QMAKE_CXXFLAGS += -stdlib=libc++
QMAKE_LFLAGS += -stdlib=libc++

LIBS += -lpthread

SOURCES += \
        main.cpp

HEADERS += \
    PropertyProxy.hpp \
    VirtualProxy.hpp \
    CommunicationProxy.hpp
