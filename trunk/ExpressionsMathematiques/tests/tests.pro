# -------------------------------------------------
# Project created by QtCreator 2009-09-29T22:07:38
# -------------------------------------------------
QT += testlib
QT -= gui
TARGET = MathExp_tests
CONFIG += console
CONFIG -= app_bundle
TEMPLATE = app
SOURCES += mathexp_tests.cpp
HEADERS += mathexp_tests.h

LIBS += -L../.. -lMathExp

DESTDIR = ../../
