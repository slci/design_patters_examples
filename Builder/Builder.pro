TEMPLATE = app
CONFIG += console c++1z
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -Wextra -Werror -pedantic -Wconversion

SOURCES += main.cpp \
    PersonBuilder/Person.cpp \
    PersonBuilder/PersonBuilder.cpp \
    PersonBuilder/PersonJobBuilder.cpp \
    PersonBuilder/PersonAddressBuilder.cpp

HEADERS += \
    XMLBuilder.hpp \
    GroovyStyleHTMLBuilder.hpp \
    PersonBuilder/Person.hpp \
    PersonBuilder/PersonBuilder.hpp \
    PersonBuilder/PersonJobBuilder.hpp \
    PersonBuilder/PersonAddressBuilder.hpp
