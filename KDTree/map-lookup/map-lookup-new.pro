#-------------------------------------------------
#
# Project created by QtCreator 2015-12-29T12:20:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = map-lookup
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
        mainwindow.cpp\
        ../src/KDTree.h

HEADERS  += mainwindow.h\
    ../src/KDTree.h \
    ../src/BoundedPQueue.h

FORMS    += mainwindow.ui

