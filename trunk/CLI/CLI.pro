CONFIG += release
TARGET = Icare-cli
CONFIG += console
QT -= gui
TEMPLATE = app
SOURCES += main.cpp \
    cli.cpp
DESTDIR = ../
LIBS += -L.. \
    -lAnalyse
HEADERS += cli.h
