#-------------------------------------------------
#
# Project created by QtCreator 2015-09-12T08:40:51
#
#-------------------------------------------------

QT       += core gui
QMAKE_CXXFLAGS += -std=gnu++0x


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CG_task1
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    editedtablemodel.cpp \
    newrowdialog.cpp \
    diagramwindow.cpp

HEADERS  += mainwindow.h \
    editedtablemodel.h \
    newrowdialog.h \
    diagramwindow.h

FORMS    += mainwindow.ui \
    newrowdialog.ui \
    diagramwindow.ui
