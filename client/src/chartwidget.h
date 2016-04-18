#pragma once

#include <QtWidgets/QWidget>
#include "log.h"
#include "config.h"

#include <QtCore/QList>

class ChartWidget
	: public QWidget, public Log, public Config
{
	Q_OBJECT

public:
	ChartWidget(const QString& name, QWidget* parent = 0);
	~ChartWidget();

public slots:
	void updateData();

protected:
	void paintEvent(QPaintEvent* event) Q_DECL_OVERRIDE;

private:
	QColor genColor(int min, int max, int val);
	QString name;

	QList<int> timeList;
	int maxValue;
	int widthValue;
	int sumSize;
	int historySize;

	QColor colorBlack;
	QColor colorWhite;
	QColor colorRed;
	QColor colorOrange;
	QColor colorYellow;
	QColor colorGreen;
	QColor colorCyan;
	QColor colorBlue;
	QColor colorPurple;

};
