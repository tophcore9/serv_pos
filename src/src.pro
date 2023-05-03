#-------------------------------------------------
#
# Project created by QtCreator 2023-04-30T18:51:42
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = src
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    clients.cpp \
    orders.cpp \
    dishes.cpp \
    addclientform.cpp \
    adddishform.cpp \
    addorderform.cpp \
    categories.cpp \
    menu.cpp \
    categoriesform.cpp \
    menuform.cpp

HEADERS  += mainwindow.h \
    clients.h \
    orders.h \
    dishes.h \
    addclientform.h \
    adddishform.h \
    addorderform.h \
    categories.h \
    menu.h \
    categoriesform.h \
    menuform.h
