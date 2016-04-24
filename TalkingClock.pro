#-------------------------------------------------
#
# Project created by QtCreator 2016-04-22T15:02:59
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TalkingClock
TEMPLATE = app


SOURCES += main.cpp\
        talkingclock.cpp \
    imageviewer.cpp \
    encapsulator.cpp \
    gpio/GPIO.cpp \
    gpio/PWM.cpp \
    gpio/util.cpp

HEADERS  += talkingclock.h \
    imageviewer.h \
    encapsulator.h \
    gpio/GPIO.h \
    gpio/PWM.h \
    gpio/util.h

FORMS    += talkingclock.ui
