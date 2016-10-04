#include "config.h"

#include <QtCore/QStandardPaths>
#include <QtCore/QFile>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonArray>

QJsonObject Config::config;

Config::Config()
{
}

Config::~Config()
{
}

bool Config::loadFromFileByName(const QString& fileName)
{
	QString configPath = QStandardPaths::locate(QStandardPaths::ConfigLocation, fileName, QStandardPaths::LocateFile);
	if (configPath == QString())
		return false;

	return loadFromFileByPath(configPath);
}

bool Config::loadFromFileByPath(const QString& filePath)
{
	QFile loadFile(filePath);
	if (!loadFile.open(QIODevice::ReadOnly))
		return false;

	QByteArray saveData = loadFile.readAll();
	QJsonDocument jConfig(QJsonDocument::fromJson(saveData));
	if (jConfig.isEmpty() || !jConfig.isObject())
		return false;

	config = jConfig.object();

	return true;
}

QString Config::getString(const QString& name)
{
	return findKey(name).toString();
}

int Config::getInt(const QString& name)
{
	return findKey(name).toInt();
}

bool Config::getBool(const QString& name)
{
	return findKey(name).toBool();
}

double Config::getDouble(const QString& name)
{
	return findKey(name).toDouble();
}

QVariant Config::getVariant(const QString& name)
{
	return findKey(name).toVariant();
}

QColor Config::getColor(const QString& name)
{
	QColor color;

	QJsonArray jArr = findKey(name).toArray();

	if (jArr.size() == 3)
		color.setRgb(jArr.at(0).toInt(), jArr.at(1).toInt(), jArr.at(2).toInt());

	return color;
}

bool Config::keyExist(const QString& name)
{
	return !findKey(name).isUndefined();
}

bool Config::isLoaded()
{
	return !config.empty();
}

QJsonValue Config::findKey(const QString& name)
{
	QStringList strList = name.split('/', QString::SkipEmptyParts);

	QJsonValue jVal(config);
	for (QStringList::const_iterator sIter = strList.constBegin(); sIter != strList.constEnd(); ++sIter)
	{
		QJsonObject jObj = jVal.toObject();
		jVal = jObj.value(*sIter);
	}

	return jVal;
}
