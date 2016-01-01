# -------------------------------------------------
# Project created by QtCreator 2010-05-16T13:21:00
# -------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = color-naming
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp \
    mainwindow.cpp \
    ../src/KDTree.h
HEADERS += mainwindow.h \
    ../src/KDTree.h \
    ../src/BoundedPQueue.h

FORMS += \
    mainwindow.ui
