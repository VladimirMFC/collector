#include "log.h"
#include "config.h"
#include "application.h"
#include "mainwindow.h"

#include <QtWidgets/QApplication>
#include <QtCore/QCommandLineParser>

int main(int argc, char** argv)
{
	Application app(argc, argv);
	app.setApplicationName("Collector System Client");
	app.setApplicationVersion("1.0");

	QCommandLineParser parser;
	parser.setApplicationDescription("Collector System Client");
	parser.addHelpOption();
	parser.addVersionOption();

	QCommandLineOption configFileOption(QStringList() << "c" << "config", "Load config file from <path>.", "path");
	parser.addOption(configFileOption);
	QCommandLineOption logFileOption(QStringList() << "l" << "log", "Open log file on <path>.", "path");
	parser.addOption(logFileOption);

	parser.process(app);

	bool logOpened;
	if (parser.isSet(logFileOption))
	{
		logOpened = Log::openLogByFilePath(parser.value(logFileOption));
	}
	else
	{
		logOpened = Log::openLogByFileName("clc.log");
	}

	if (!logOpened)
	{
		Log::logCrit("Cant open log file");

		return EXIT_SUCCESS;
	}

	bool configLoaded;
	if (parser.isSet(configFileOption))
	{
		configLoaded = Config::loadConfigFromFileByPath(parser.value(configFileOption));
	}
	else
	{
		configLoaded = Config::loadConfigFromFileByName("clc.conf");
	}

	if (!configLoaded)
	{
		Log::logCrit("Cant load config file");

		return EXIT_SUCCESS;
	}

	MainWindow win;
	win.showFullScreen();

	return app.exec();
}
