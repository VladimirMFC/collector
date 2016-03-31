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
	QString name;
	QList<int> timeList;

};
