#include "config.h"

#include <QtCore/QStandardPaths>
#include <QtCore/QFile>
#include <QtCore/QJsonDocument>

QJsonObject Config::config;

Config::Config()
{
}

Config::~Config()
{
}

bool Config::loadConfigFromFileByName(const QString& fileName)
{
	QString configPath = QStandardPaths::locate(QStandardPaths::ConfigLocation, fileName, QStandardPaths::LocateFile);
	if (configPath == QString())
	{
		return false;
	}

	return loadConfigFromFileByPath(configPath);
}

bool Config::loadConfigFromFileByPath(const QString& filePath)
{
	QFile loadFile(filePath);
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

bool Config::saveConfigToFileByName(const QString& fileName)
{
	QString configPath = QStandardPaths::locate(QStandardPaths::ConfigLocation, "", QStandardPaths::LocateDirectory);
	if (configPath == QString())
	{
		return false;
	}

	return saveConfigToFileByPath(configPath + fileName);
}

bool Config::saveConfigToFileByPath(const QString& filePath)
{
	QFile saveFile(filePath);
	if (!saveFile.open(QIODevice::WriteOnly))
	{
		return false;
	}

	QJsonDocument saveDoc(config);
	saveFile.write(saveDoc.toJson());

	return true;
}

QString Config::getConfigString(const QString& name)
{
	return config[name].toString();
}

int Config::getConfigInt(const QString& name)
{
	return config[name].toInt();
}

bool Config::getConfigBool(const QString& name)
{
	return config[name].toBool();
}

double Config::getConfigDouble(const QString& name)
{
	return config[name].toDouble();
}

QVariant Config::getConfigVariant(const QString& name)
{
	return config[name].toVariant();
}

void Config::setConfigValue(const QString& name, const QString& value)
{
	config[name] = value;
}

bool Config::configLoaded()
{
	return !config.empty();
}
