#include "application.h"

Application::Application(int& argc, char** argv)
	: QApplication(argc, argv), Log(), Config()
{
}

Application::~Application()
{
	Log::closeFile();
}
