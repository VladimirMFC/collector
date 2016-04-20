#pragma once

#include <QtCore/QString>
#include <QtCore/QJsonObject>
#include <QtCore/QVariant>
#include <QtGui/QColor>

class Config
{
public:
	Config();
	~Config();

	static bool loadFromFileByName(const QString& fileName);
	static bool loadFromFileByPath(const QString& filePath);

	static QString getString(const QString& name);
	static int getInt(const QString& name);
	static bool getBool(const QString& name);
	static double getDouble(const QString& name);
	static QVariant getVariant(const QString& name);
	static QColor getColor(const QString& name);

	static bool keyExist(const QString& name);

	static bool isLoaded();

private:
	static QJsonValue findKey(const QString& name);

	static QJsonObject config;

};
