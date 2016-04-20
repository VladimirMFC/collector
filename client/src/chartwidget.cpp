#include "chartwidget.h"

#include <QtGui/QPainter>
#include <QtGui/QStaticText>
#include <QtCore/QTimer>
#include <QtCore/QTime>

ChartWidget::ChartWidget(const QString& name, QWidget* parent)
	: QWidget(parent), Log(), Config(),
	name(name), maxValue(100), sumSize(10), historySize(1000), fontName("DroidSansMonoForPowerline")
{
	colorBlack = QColor(29, 31, 33);
	colorWhite = QColor(197, 200, 198);
	colorRed = QColor(204, 102, 102);
	colorOrange = QColor(222, 147, 95);
	colorYellow = QColor(240, 198, 116);
	colorGreen = QColor(181, 189, 104);
	colorCyan = QColor(138, 190, 183);
	colorBlue = QColor(129, 162, 190);
	colorPurple = QColor(187, 148, 187);

	initConfigData();

	setAutoFillBackground(true);
	QPalette pal = palette();
	pal.setColor(QPalette::Window, colorBlack);
	setPalette(pal);

	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(updateData()));
	timer->start(1000);

	QTime time = QTime::currentTime();
	qsrand((uint)time.msec());
}

ChartWidget::~ChartWidget()
{
}

void ChartWidget::updateData()
{
	timeList.prepend(qrand() % maxValue);

	if (timeList.size() > historySize)
	{
		timeList.removeLast();
	}

	update(rect());
}

void ChartWidget::paintEvent(QPaintEvent*)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.setRenderHint(QPainter::TextAntialiasing);
	painter.setRenderHint(QPainter::HighQualityAntialiasing);

	int barWidth = height() / 10;

	int f = 0;
	for (int i = 0; i < sumSize && i < timeList.size(); ++i)
	{
		f += timeList[i];
	}

	f = (timeList.size() < sumSize && timeList.size() != 0) ? f / timeList.size() : f / sumSize;

	QString sst(name);
	sst += QString(": t ") + QString::number(f) + QString("ms\n");

	QDateTime dt = QDateTime::currentDateTime();
	sst += dt.toString("dd.MM hh:mm:ss");

	painter.setPen(genColor(0, maxValue, f));
	painter.setFont(QFont(fontName, height() / 3));

	QRect trc;
	painter.drawText(QRect(barWidth / 2, 0, width(), height()), Qt::AlignVCenter, sst, &trc);

	for (int i = 0, x = width() - 1; i < timeList.size() && x > trc.width() + (2 * barWidth) + 2; ++i, x -= barWidth + 1)
	{
		QRectF rc(QPointF(0.0, 1.0), QPointF((float)barWidth, (float)height() - ((float)height() / (float)maxValue * (float)timeList[i])));
		if (rc.height() < 2)
		{
			rc.setHeight(2);
		}
		if (rc.height() > height() - 2)
		{
			rc.setHeight(height() - 2);
		}
		rc.moveBottom(height() - 1);
		rc.moveRight(x);

		painter.fillRect(rc, genColor(0, maxValue, timeList[i]));
	}
}

void ChartWidget::initConfigData()
{
	if (Config::keyExist("history"))
	{
		historySize = Config::getInt("history");
	}

	if (Config::keyExist("font"))
	{
		fontName = Config::getString("font");
	}

	if (Config::keyExist("colors/black"))
	{
		colorBlack = Config::getColor("colors/black");
	}
	if (Config::keyExist("colors/white"))
	{
		colorWhite = Config::getColor("colors/white");
	}
	if (Config::keyExist("colors/red"))
	{
		colorRed = Config::getColor("colors/red");
	}
	if (Config::keyExist("colors/orange"))
	{
		colorOrange = Config::getColor("colors/orange");
	}
	if (Config::keyExist("colors/yellow"))
	{
		colorYellow = Config::getColor("colors/yellow");
	}
	if (Config::keyExist("colors/green"))
	{
		colorGreen = Config::getColor("colors/green");
	}
	if (Config::keyExist("colors/cyan"))
	{
		colorCyan = Config::getColor("colors/cyan");
	}
	if (Config::keyExist("colors/blue"))
	{
		colorBlue = Config::getColor("colors/blue");
	}
	if (Config::keyExist("colors/purple"))
	{
		colorPurple = Config::getColor("colors/purple");
	}
}

QColor ChartWidget::genColor(int min, int max, int val)
{
	int cur = 0, step = (max - min) / 5;

	cur += step;
	if (val <= cur)
	{
		return colorBlue;
	}

	cur += step;
	if (val <= cur)
	{
		return colorGreen;
	}

	cur += step;
	if (val <= cur)
	{
		return colorYellow;
	}

	cur += step;
	if (val <= cur)
	{
		return colorOrange;
	}

	return colorRed;
}
