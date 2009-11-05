# -------------------------------------------------
# Project created by QtCreator 2009-09-29T21:02:22
# -------------------------------------------------
CONFIG += release
QT -= gui
TARGET = Analyse
TEMPLATE = lib
DEFINES += ANALYSESEMANTIQUE_LIBRARY ANALYSESYNTAXIQUE_LIBRARY
SOURCES += analysesyntaxique.cpp \
    analysesemantique.cpp
HEADERS += Analyse_global.h \
    analysesyntaxique.h \
    analysesemantique.h
DESTDIR = ../
