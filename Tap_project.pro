TEMPLATE = app
CONFIG += console
CONFIG -= qt
//QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp

HEADERS += \
    headers/Tap.h \
    headers/Tapx.h

OTHER_FILES += \
    README.md \
    LICENSE.txt

