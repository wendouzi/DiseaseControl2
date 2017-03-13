#-------------------------------------------------
#
# Project created by QtCreator 2017-03-12T11:10:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DiseaseControl2
TEMPLATE = app


SOURCES += src/main.cpp\
        src/mainwindow.cpp \
    src/imageviewer.cpp \
    src/imagemanager.cpp \
    src/config.cpp

HEADERS  += src/mainwindow.h \
    src/imageviewer.h \
    src/imagemanager.h \
    src/config.h

FORMS    += src/mainwindow.ui

RESOURCES += resource/imgqrc.qrc
