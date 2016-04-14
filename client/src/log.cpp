#include "log.h"

Log::Log(const QString& filename)
	: m_filename(filename), m_file(0), m_stream(0)
{
	create();
}

Log::~Log()
{
	destroy();
}

Log* Log::getInstance()
{
	static CLog* instance = new CLog("application.log");

	return instance;
}

void Log::freeInstance()
{
	delete this;
}

void Log::information(const QString& message)
{
	writeMessage(MT_INFO, message);

	m_file->flush();
}

void Log::warning(const QString& message)
{
	writeMessage(MT_WARN, message);

	m_file->flush();
}

void Log::error(const QString& message)
{
	writeMessage(MT_ERR, message);

	m_file->flush();
}

void Log::create()
{
	m_file = new QFile(m_filename);
	if (!m_file->open(QIODevice::WriteOnly | QIODevice::Text))
	{
		return;
	}

	m_stream = new QTextStream(m_file);
	m_stream->setCodec("UTF-8");

	writeHeader();
}

void Log::destroy()
{
	writeFooter();

	m_file->close();

	delete m_stream;
	delete m_file;
}

QString Log::getTimeStamp()
{
	QDateTime dt = QDateTime::currentDateTime();

	return dt.toString("yyyy/MM/dd hh:mm:ss");
}

void Log::writeHeader()
{
	writeMessage(MT_INFO, QObject::tr("α"));

	m_stream->flush();
	m_file->flush();
}

void Log::writeFooter()
{
	writeMessage(MT_INFO, QObject::tr("Ω"));

	m_stream->flush();
	m_file->flush();
}

void Log::writeMessage(EMessageType type, const QString& message)
{
	(*m_stream) << getTimeStamp() << "  ";

	switch (type)
	{
	case MT_INFO:
		(*m_stream) << QObject::tr("Info       ");
		break;

	case MT_WARN:
		(*m_stream) << QObject::tr("Warning    ");
		break;

	case MT_ERR:
		(*m_stream) << QObject::tr("Error      ");
		break;

	default:
		(*m_stream) << QObject::tr("Unknown    ");
		break;
	}

	(*m_stream) << message << ".\n";

	m_stream->flush();
	m_file->flush();
}
