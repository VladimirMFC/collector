#include "config.h"

#include <QtCore/QStandardPaths>
#include <QtCore/QFile>
#include <QtCore/QJsonDocument>

Config::Config()
{
}

Config::~Config()
{
}

bool Config::loadFromFile(const QString& file)
{
	QString configFile = QStandardPaths::locate(QStandardPaths::ConfigLocation, file, QStandardPaths::LocateFile);
	if (configFile == QString())
	{
		return false;
	}

	QFile loadFile(configFile);
	if (!loadFile.open(QIODevice::ReadOnly))
	{
		return false;
	}

	QByteArray saveData = loadFile.readAll();
	QJsonDocument jConfig(QJsonDocument::fromJson(saveData));
	if (jConfig.isEmpty() || !jConfig.isObject())
	{
		return false;
	}

	config = jConfig.object();

	return true;
}

bool Config::saveToFile(const QString& file)
{
	QString configLocation = QStandardPaths::locate(QStandardPaths::ConfigLocation, "", QStandardPaths::LocateDirectory);
	if (configLocation == QString())
	{
		return false;
	}

	QFile saveFile(configLocation + file);
	if (!saveFile.open(QIODevice::WriteOnly))
	{
		return false;
	}

	QJsonDocument saveDoc(config);
	saveFile.write(saveDoc.toJson());

	return true;
}

QString Config::getValue(const QString& name)
{
	return config[name].toString();
}

void Config::setValue(const QString& name, const QString& value)
{
	config[name] = value;
}
