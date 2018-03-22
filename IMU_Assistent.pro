#-------------------------------------------------
#
# Project created by QtCreator 2018-03-17T13:54:57
#
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = IMU_Assistent
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


SOURCES += main.cpp \
    mainwindow.cpp \
    monitorThread.cpp \
    myCOM.cpp

HEADERS  += mainwindow.h \
    monitorThread.h \
    myCOM.h

FORMS    += mainwindow.ui

CONFIG += qwt
DEFINES += QT_DLL QWT_DLL
LIBS += -L"C:\Qt\Qt5.8.0\build-qwt-Desktop_Qt_5_8_0_MinGW_32bit-Debug\lib" -lqwtd
LIBS += -L"C:\Qt\Qt5.8.0\build-qwt-Desktop_Qt_5_8_0_MinGW_32bit-Debug\lib" -lqwt
INCLUDEPATH += C:\Qt\Qt5.8.0\5.8\mingw53_32\include\QWT

