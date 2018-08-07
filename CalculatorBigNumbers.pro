#-------------------------------------------------
#
# Project created by QtCreator 2017-10-04T01:19:16
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Calculator' 'Big' 'Numbers
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    labelinformation.cpp \
    Operations.cpp

HEADERS  += mainwindow.h \
    Operations.h

FORMS    += mainwindow.ui

CONFIG += mobility
MOBILITY = 

RESOURCES += \
    resources.qrc

