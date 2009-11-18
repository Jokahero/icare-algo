# -------------------------------------------------
# Project created by QtCreator 2009-09-29T21:02:22
# -------------------------------------------------
CONFIG += release
QT -= gui
TARGET = Analyse
TEMPLATE = lib
DEFINES += ANALYSESEMANTIQUE_LIBRARY \
    ANALYSESYNTAXIQUE_LIBRARY
SOURCES += analysesyntaxique.cpp \
    analysesemantique.cpp \
    glossaire.cpp
HEADERS += Analyse_global.h \
    analysesyntaxique.h \
    analysesemantique.h \
    glossaire.h \
    erreuranalyse.h
DESTDIR = ../
