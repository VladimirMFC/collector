QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = clc
TEMPLATE = app

unix:QMAKE_CXXFLAGS += -std=c++11

CODECFORSRC = UTF-8
CODECFORTR = UTF-8

SOURCES += src/*.cpp
HEADERS += src/*.h
DISTFILES += conf/*
