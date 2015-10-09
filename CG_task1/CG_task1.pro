#-------------------------------------------------
#
# Project created by QtCreator 2015-09-12T08:40:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CG_task1
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    editedtablemodel.cpp \
    newrowdialog.cpp

HEADERS  += mainwindow.h \
    editedtablemodel.h \
    newrowdialog.h

FORMS    += mainwindow.ui \
    newrowdialog.ui
