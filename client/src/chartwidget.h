#pragma once

#include <QtWidgets/QWidget>
#include <QtCore/QList>

class ChartWidget
	: public QWidget
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

	QColor colorBlack;
	QColor colorWhite;
	QColor colorRed;
	QColor colorOrange;
	QColor colorYellow;
	QColor colorGreen;
	QColor colorLBlue;
	QColor colorDBlue;
	QColor colorPurple;

};
