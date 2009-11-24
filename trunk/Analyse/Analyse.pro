# -------------------------------------------------
# Project created by QtCreator 2009-09-29T21:02:22
# -------------------------------------------------
CONFIG += release
TARGET = Analyse
TEMPLATE = lib
DEFINES += ANALYSESEMANTIQUE_LIBRARY \
    ANALYSESYNTAXIQUE_LIBRARY
SOURCES += analysesyntaxique.cpp \
    analysesemantique.cpp \
    glossaire.cpp \
    dictionnaire.cpp \
    instruction.cpp
HEADERS += Analyse_global.h \
    analysesyntaxique.h \
    analysesemantique.h \
    glossaire.h \
    erreuranalyse.h \
    dictionnaire.h \
    instruction.h
DESTDIR = ../
