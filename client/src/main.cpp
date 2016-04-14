#include "log.h"
#include "config.h"
#include "mainwindow.h"

#include <QtWidgets/QApplication>
#include <QtWidgets/QMessageBox>

Config conf;

int main(int argc, char** argv)
{
	QApplication a(argc, argv);

	if (!conf.loadFromFile("clc.conf"))
	{
		QMessageBox mb;
		mb.setIcon(QMessageBox::Critical);
		mb.setWindowTitle("Collector");
		mb.setText("Cant load config file");
		mb.exec();

		return EXIT_SUCCESS;
	}

	MainWindow w;
	w.showFullScreen();

	return a.exec();
}
