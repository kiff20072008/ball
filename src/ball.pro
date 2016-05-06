#-------------------------------------------------
#
# Project created by QtCreator 2016-04-26T10:03:59
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ball
TEMPLATE = app


SOURCES += main.cpp \
    ball.cpp

HEADERS  += \
    ball.h
QMAKE_LFLAGS_RELEASE += -static -static-libgcc
