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
	src/mainwindow.cpp \
	src/chartwidget.cpp \
	src/config.cpp \
	src/log.cpp

HEADERS += \
	src/mainwindow.h \
	src/chartwidget.h \
	src/config.h \
	src/log.h

DISTFILES += \
	clc.conf
