QT += core gui widgets

TARGET = clc
TEMPLATE = app

unix:QMAKE_CXXFLAGS += -std=c++11

CODECFORSRC = UTF-8
CODECFORTR = UTF-8

SOURCES += \
	src/main.cpp \
	src/mainwindow.cpp

HEADERS += \
	src/mainwindow.h

DISTFILES += conf/*
