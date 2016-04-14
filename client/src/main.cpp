#include "log.h"
#include "config.h"
#include "mainwindow.h"

#include <QtWidgets/QApplication>

int main(int argc, char** argv)
{
	QApplication a(argc, argv);
	MainWindow w;
	w.showMaximized();

	return a.exec();
}
