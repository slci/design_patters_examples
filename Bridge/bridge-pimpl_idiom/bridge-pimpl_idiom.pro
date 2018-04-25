TEMPLATE = app
CONFIG += console c++1z
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -Wextra -Werror -pedantic -Wconversion

SOURCES += \
        main.cpp \
    Person.cpp

HEADERS += \
    Person.hpp
