#-------------------------------------------------
#
# Project created by QtCreator 2015-11-01T22:10:27
#
#-------------------------------------------------

QT       += core gui
QT += opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = PlotTry
TEMPLATE = app
target.path = /home/pi/ECG
INSTALLS += target


SOURCES += main.cpp\
        mainwindow.cpp \
    qcustomplot.cpp

HEADERS  += mainwindow.h \
    qcustomplot.h

FORMS    += mainwindow.ui

CONFIG += c++11

CONFIG += console

CONFIG += release

unix|win32: LIBS += -lserial

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../usr/lib/release/ -lserial
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../usr/lib/debug/ -lserial
else:unix: LIBS += -L$$PWD/../../../usr/lib/ -lserial

INCLUDEPATH += $$PWD/../../../usr/include
DEPENDPATH += $$PWD/../../../usr/include


