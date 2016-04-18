#pragma once

#include <QtCore/QString>
#include <QtCore/QJsonObject>
#include <QtCore/QVariant>

class Config
{
public:
	Config();
	~Config();

	static bool loadConfigFromFileByName(const QString& fileName);
	static bool loadConfigFromFileByPath(const QString& filePath);
	static bool saveConfigToFileByName(const QString& fileName);
	static bool saveConfigToFileByPath(const QString& filePath);

	static QString getConfigString(const QString& name);
	static int getConfigInt(const QString& name);
	static bool getConfigBool(const QString& name);
	static double getConfigDouble(const QString& name);
	static QVariant getConfigVariant(const QString& name);
	static void setConfigValue(const QString& name, const QString& value);

	static bool configLoaded();

private:
	static QJsonObject config;

};
