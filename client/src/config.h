#pragma once

#include <QtCore/QString>
#include <QtCore/QJsonObject>

class Config
{
public:
	Config();
	~Config();

	bool loadFromFile(const QString& file);
	bool saveToFile(const QString& file);

	QString getValue(const QString& name);
	void setValue(const QString& name, const QString& value);

private:
	QJsonObject config;

};
