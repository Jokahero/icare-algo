# -------------------------------------------------
# Project created by QtCreator 2009-09-29T21:02:22
# -------------------------------------------------
CONFIG += release
QT -= gui
TARGET = MathExp
TEMPLATE = lib
DEFINES += MATHEXP_LIBRARY \
    ARBRE_LIB
SOURCES += mathexp.cpp \
    arbre.cpp
HEADERS += mathexp.h \
    MathExp_global.h \
    arbre.h
DESTDIR = ../
