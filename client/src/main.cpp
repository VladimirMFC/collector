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
		logOpened = Log::openByFilePath(parser.value(logFileOption));
	else
		logOpened = Log::openByFileName("clc.log");

	if (!logOpened)
	{
		Log::crit("Cant open log file");
		return EXIT_SUCCESS;
	}

	bool configLoaded;
	if (parser.isSet(configFileOption))
		configLoaded = Config::loadFromFileByPath(parser.value(configFileOption));
	else
		configLoaded = Config::loadFromFileByName("clc.conf");

	if (!configLoaded)
	{
		Log::crit("Cant load config file");
		return EXIT_SUCCESS;
	}

	bool startFullscreen = true;
	if (Config::keyExist("window/fullscreen"))
		startFullscreen = Config::getBool("window/fullscreen");

	MainWindow win;
	if (startFullscreen)
		win.showFullScreen();
	else
		win.showMaximized();

	return app.exec();
}
