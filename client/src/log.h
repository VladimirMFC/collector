#pragma once

#include <QtCore/QString>
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtCore/QDateTime>

class Log
{
public:
	enum EMessageType
	{
		MT_INFO,
		MT_WARN,
		MT_ERR
	};

	Log(const QString& filename);
	~Log();

	static Log* getInstance();
	void freeInstance();

	void information(const QString& message);
	void warning(const QString& message);
	void error(const QString& message);

private:
	Log(const Log& log);
	const Log& operator= (const Log& rhs);

	QString m_filename;
	QFile *m_file;
	QTextStream *m_stream;

	void create();
	void destroy();

	QString getTimeStamp();

	void writeHeader();
	void writeFooter();
	void writeMessage(EMessageType type, const QString& message);

};
