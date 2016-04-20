#pragma once

#include <QtWidgets/QMainWindow>
#include "log.h"
#include "config.h"

class MainWindow
	: public QMainWindow, public Log, public Config
{
	Q_OBJECT

public:
	MainWindow(QWidget* parent = nullptr);
	~MainWindow();

public slots:
	void keyPressEvent(QKeyEvent* ke) Q_DECL_OVERRIDE;

private:
	void initConfigData();

	int colCount;

};
