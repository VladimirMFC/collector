#include "chartwidget.h"

#include <QtGui/QPainter>
#include <QtGui/QStaticText>
#include <QtCore/QTimer>
#include <QtCore/QTime>

ChartWidget::ChartWidget(const QString& name, QWidget* parent)
	: QWidget(parent), Log(), Config(),
	name(name), maxValue(100), widthValue(10), sumSize(10), historySize(1000)
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
	/*if (timeList.size() > 1)
	{
		if (timeList[0] < maxValue && timeList[0] > 0)
		{
			if (timeList[0] > timeList[1])
			{
				timeList.prepend(timeList[0] + 1);
			}
			else
			{
				timeList.prepend(timeList[0] - 1);
			}
		}
		else
		{
			if (timeList[0] == maxValue)
			{
				timeList.prepend(timeList[0] - 1);
			}
			else
			{
				timeList.prepend(timeList[0] + 1);
			}
		}
	}
	else
	{
		timeList.prepend(qrand() % maxValue);
		if (qrand() % 1 == 0)
		{
			timeList.prepend(timeList[0] - 1);
		}
		else
		{
			timeList.prepend(timeList[0] + 1);
		}
	}*/

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

	int f = 0;
	for (int i = 0; i < sumSize && i < timeList.size(); ++i)
	{
		f += timeList[i];
	}

	f = (timeList.size() < sumSize && timeList.size() != 0) ? f / timeList.size() : f / sumSize;

	QString sst(name);
	sst += QString("\nt ") + QString::number(f) + QString("ms");

	painter.setPen(genColor(0, maxValue, f));
	painter.setFont(QFont("DroidSansMonoForPowerline", height() / 3));

	QRect trc;
	painter.drawText(QRect(widthValue, 0, width(), height()), Qt::AlignVCenter, sst, &trc);

	for (int i = 0, x = width() - 1; i < timeList.size() && x > trc.width() + (2 * widthValue) + 2; ++i, x -= widthValue + 1)
	{
		QRectF rc(QPointF(0.0, 1.0), QPointF((float)widthValue, (float)height() - ((float)height() / (float)maxValue * (float)timeList[i])));
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

	//painter.drawRect(rect());
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
