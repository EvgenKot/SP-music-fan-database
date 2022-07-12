#-------------------------------------------------
#
# Project created by QtCreator 2022-07-04T18:37:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SP-music-fan-database
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    about.cpp \
    report.cpp \
    process.cpp \
    author.cpp \
    disk.cpp \
    song.cpp

HEADERS  += mainwindow.h \
    about.h \
    report.h \
    list.h \
    author.h \
    disk.h \
    song.h \
    process.h

FORMS    += mainwindow.ui \
    about.ui \
    report.ui
