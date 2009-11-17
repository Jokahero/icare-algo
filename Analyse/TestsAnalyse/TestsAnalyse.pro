CONFIG += release
QT += testlib
QT -= gui
TARGET = Analyse_tests
CONFIG += console
CONFIG -= app_bundle
TEMPLATE = app
SOURCES += analyse_tests.cpp
HEADERS += analyse_tests.h

LIBS += -L../.. -lAnalyse

DESTDIR = ../../
