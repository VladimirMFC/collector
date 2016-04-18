#pragma once

#include <QtWidgets/QApplication>
#include "log.h"
#include "config.h"

class Application
	: public QApplication, public Log, public Config
{
	Q_OBJECT

public:
	Application(int& argc, char** argv);
	~Application();

};
