TARGET = Icare
CONFIG -= app_bundle
CONFIG += release
TEMPLATE = app
SOURCES += main.cpp
DESTDIR = ../
LIBS += -L.. \
    -lAnalyse \
    -lGUI
RESOURCES += Splash.qrc
