#-------------------------------------------------
#
# Project created by QtCreator 2009-10-20T16:45:27
#
#-------------------------------------------------
CONFIG += release

TARGET = Icare
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp

DESTDIR = ../

LIBS += -L.. -lAnalyse -lGUI -lMathExp
