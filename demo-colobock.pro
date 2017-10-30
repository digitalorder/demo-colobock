#-------------------------------------------------
#
# Project created by QtCreator 2017-10-23T21:59:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = demo-colobock
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += Dialogs \
    Models \
    ViewControllers \
    Logic \
    Shared

SOURCES += main.cpp\
    Dialogs/mainwindow.cpp \
    Dialogs/configdialog.cpp \
    Dialogs/infodialog.cpp \
    Models/rockersmodel.cpp \
    Models/locksmodel.cpp \
    Models/logger.cpp \
    ViewControllers/rocker.cpp \
    ViewControllers/rockersmatrix.cpp \
    ViewControllers/lock.cpp \
    ViewControllers/locksarray.cpp \
    Logic/rockerslogic.cpp \
    Logic/lockslogic.cpp \
    Logic/winlogic.cpp \
    Shared/primitivetypes.cpp

HEADERS  += \
    Dialogs/mainwindow.h \
    Dialogs/configdialog.h \
    Dialogs/infodialog.h \
    Models/rockersmodel.h \
    Models/locksmodel.h \
    Models/logger.h \
    ViewControllers/rocker.h \
    ViewControllers/rockersmatrix.h \
    ViewControllers/lock.h \
    ViewControllers/locksarray.h \
    Logic/rockerslogic.h \
    Logic/lockslogic.h \
    Logic/winlogic.h \
    Shared/primitivetypes.h

RESOURCES += \
    resources.qrc
