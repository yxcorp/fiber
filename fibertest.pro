#-------------------------------------------------
#
# Project created by QtCreator 2016-04-26T10:49:20
#
#-------------------------------------------------

QT       += core gui printsupport
QT += sql
QT += multimedia
QT += multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = fibertest
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    photopreviewarea.cpp \
    configarea.cpp \
    createanalyzewizard.cpp

HEADERS  += mainwindow.h \
    photopreviewarea.h \
    configarea.h \
    createanalyzewizard.h \
    enumsettings.h

FORMS    += mainwindow.ui

TRANSLATIONS += cn.ts

RESOURCES += \
    resource.qrc




