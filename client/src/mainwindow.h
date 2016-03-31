#pragma once

#include <QtWidgets/QMainWindow>

class MainWindow
	: public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget* parent = 0);
	~MainWindow();

public slots:
	void keyPressEvent(QKeyEvent* ke);

};
