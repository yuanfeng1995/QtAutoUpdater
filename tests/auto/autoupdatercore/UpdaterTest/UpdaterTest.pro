TEMPLATE = app

QT += testlib autoupdatercore
QT -= gui

CONFIG += console
CONFIG -= app_bundle

TARGET = tst_updater

HEADERS +=

SOURCES += \
	tst_updater.cpp

DEFINES += SRCDIR=\\\"$$PWD/\\\"

include($$PWD/../../testrun.pri)
