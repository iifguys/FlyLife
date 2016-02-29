#-------------------------------------------------
#
# Project created by QtCreator 2016-02-26T15:50:45
#
#-------------------------------------------------

QT       += core gui opengl multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FlysProject
TEMPLATE = app


SOURCES += main.cpp\
    mainwindow.cpp \
    myglwidget.cpp \
    fly.cpp \
    cell.cpp \
    addnewflyform.cpp \
    statisticsform.cpp

HEADERS  += mainwindow.h \
    myglwidget.h \
    fly.h \
    cell.h \
    general_includes.h \
    addnewflyform.h \
    statisticsform.h

FORMS    += \
    addnewflyform.ui \
    statisticsform.ui \
    mainwindow.ui

RESOURCES += \
    res.qrc
