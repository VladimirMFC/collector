QT += core gui widgets

TARGET = clc
TEMPLATE = app

win32 {
	RC_FILE += win32.rc
	OTHER_FILES += win32.rc
}

win32-g++:QMAKE_CXXFLAGS += -std=c++11
unix:QMAKE_CXXFLAGS += -std=c++11

CODECFORSRC = UTF-8
CODECFORTR = UTF-8

SOURCES += \
	src/main.cpp \
	src/mainwindow.cpp

HEADERS += \
	src/mainwindow.h

DISTFILES += \
	clc.conf
