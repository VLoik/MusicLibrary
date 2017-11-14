#-------------------------------------------------
#
# Project created by QtCreator 2016-11-29T16:27:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = lab3
TEMPLATE = app

TRANSLATIONS += \
    lab3_ru.ts

SOURCES += main.cpp\
        mainwindow.cpp \
    item.cpp \
    musicmodel.cpp \
    ratingdelegate.cpp \
    albumdialog.cpp \
    artisdialog.cpp \
    ratingwidget.cpp

HEADERS  += mainwindow.h \
    item.h \
    musicmodel.h \
    ratingdelegate.h \
    albumdialog.h \
    artistdialog.h \
    ratingwidget.h

FORMS    += mainwindow.ui \
    albumdialog.ui \
    artistdialog.ui \

DISTFILES += \
    lab3_ru.ts
