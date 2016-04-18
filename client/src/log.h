#pragma once

#include <QtCore/QString>
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtCore/QDateTime>

class Log
{
public:
	Log();
	~Log();

	static bool openLogByFileName(const QString& fileName);
	static bool openLogByFilePath(const QString& filePath);
	static void closeLog();

	static void logInfo(const QString& message);
	static void logWarn(const QString& message);
	static void logCrit(const QString& message);

private:
	enum EMessageType
	{
		MT_INFO,
		MT_WARN,
		MT_CRIT
	};

	static QString fileName;
	static QFile *file;
	static QTextStream *fileStream;

	static QTextStream *consoleStream;

	static QString getTimeStamp();

	static void writeHeader();
	static void writeFooter();
	static void writeMessage(EMessageType type, const QString& message);

};
