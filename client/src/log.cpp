#include "log.h"

#include <QtCore/QStandardPaths>

QString Log::fileName;
QFile *Log::file = nullptr;
QTextStream *Log::fileStream = nullptr;
QTextStream *Log::consoleStream = nullptr;

Log::Log()
{
}

Log::~Log()
{
}

bool Log::openLogByFileName(const QString& fileName)
{
	QString logPath = QStandardPaths::locate(QStandardPaths::ConfigLocation, "", QStandardPaths::LocateDirectory);
	if (logPath == QString())
	{
		return false;
	}

	return openLogByFilePath(logPath + fileName);
}

bool Log::openLogByFilePath(const QString& filePath)
{
	file = new QFile(filePath);
	if (!file->open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
	{
		return false;
	}

	fileStream = new QTextStream(file);
	fileStream->setCodec("UTF-8");

	consoleStream = new QTextStream(stdout);
	consoleStream->setCodec("UTF-8");

	writeHeader();

	return true;
}

void Log::closeLog()
{
	writeFooter();

	file->close();

	delete fileStream;
	delete file;

	delete consoleStream;
}

void Log::logInfo(const QString& message)
{
	writeMessage(MT_INFO, message);
}

void Log::logWarn(const QString& message)
{
	writeMessage(MT_WARN, message);
}

void Log::logCrit(const QString& message)
{
	writeMessage(MT_CRIT, message);
}

QString Log::getTimeStamp()
{
	QDateTime dt = QDateTime::currentDateTime();

	return dt.toString("yyyy/MM/dd hh:mm:ss");
}

void Log::writeHeader()
{
	writeMessage(MT_INFO, QObject::tr("Started"));
}

void Log::writeFooter()
{
	writeMessage(MT_INFO, QObject::tr("Stoped"));
}

void Log::writeMessage(EMessageType type, const QString& message)
{
	(*fileStream) << getTimeStamp() << "  ";

	switch (type)
	{
	case MT_INFO:
		(*fileStream) << QObject::tr("Info: ");
		break;

	case MT_WARN:
		(*fileStream) << QObject::tr("Warning: ");
		break;

	case MT_CRIT:
		(*fileStream) << QObject::tr("Critical: ");
		break;

	default:
		(*fileStream) << QObject::tr("Unknown: ");
		break;
	}

	(*fileStream) << message << "\n";
	fileStream->flush();
	file->flush();

	if (type == MT_WARN || type == MT_CRIT)
	{
		(*consoleStream) << message << "\n";
		consoleStream->flush();
	}
}
