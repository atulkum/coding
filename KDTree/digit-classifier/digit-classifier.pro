# -------------------------------------------------
# Project created by QtCreator 2010-05-16T20:51:29
# -------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = digit-classifier
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp \
    mainwindow.cpp \
    CanvasWidget.cpp \
    ../src/KDTree.h \
    autounlock.cpp
HEADERS += mainwindow.h \
    CanvasWidget.h \
    grid.h \
    ../src/KDTree.h \
    ../src/BoundedPQueue.h \
    autounlock.h

FORMS    += mainwindow.ui \
    mainwindow.ui
