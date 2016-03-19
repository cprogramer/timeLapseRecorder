#-------------------------------------------------
#
# Project created by QtCreator 2016-03-19T16:50:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TimeLapseRecorder
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    VideoEncoder.cpp \
    YUV4MPEG2.cpp \
    MJPEG.cpp

HEADERS  += widget.h \
    VideoEncoder.h \
    YUV4MPEG2.h \
    MJPEG.h

FORMS    += widget.ui
