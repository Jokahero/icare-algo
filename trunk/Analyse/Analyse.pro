# -------------------------------------------------
# Project created by QtCreator 2009-09-29T21:02:22
# -------------------------------------------------
CONFIG += release
TARGET = Analyse
TEMPLATE = lib
QT -= gui
DEFINES += ANALYSE_LIBRARY
SOURCES += analysesyntaxique.cpp \
    analysesemantique.cpp \
    glossaire.cpp \
    dictionnaire.cpp \
    instruction.cpp \
    analyse.cpp \
    execution.cpp \
    arbre.cpp \
    mathexp.cpp \
    expressionlogique.cpp
HEADERS += Analyse_global.h \
    analysesyntaxique.h \
    analysesemantique.h \
    glossaire.h \
    dictionnaire.h \
    instruction.h \
    analyse.h \
    execution.h \
    arbre.h \
    mathexp.h \
    expressionlogique.h
DESTDIR = ../
