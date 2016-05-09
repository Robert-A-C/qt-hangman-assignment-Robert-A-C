#-------------------------------------------------
#
# Project created by QtCreator 2016-05-03T13:41:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Hangman
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    model/hangman.cpp

HEADERS  += mainwindow.h \
    model/hangman.h

FORMS    += mainwindow.ui

INCLUDEPATH += "C:/Program Files (x86)/Windows Kits/10/Include/10.0.10150.0/ucrt"
LIBS += -L"C:/Program Files (x86)/Windows Kits/10/Lib/10.0.10150.0/ucrt/x64"

RESOURCES += \
    resrouces.qrc
