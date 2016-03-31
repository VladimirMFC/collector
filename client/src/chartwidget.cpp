#include "chartwidget.h"

#include <QtGui/QPainter>
#include <QtGui/QStaticText>
#include <QtCore/QTimer>
#include <QtCore/QTime>

ChartWidget::ChartWidget(const QString& name, QWidget* parent)
	: QWidget(parent), name(name)
{
	colorBlack = QColor(29, 31, 33);
	colorWhite = QColor(197, 200, 198);
	colorRed = QColor(204, 102, 102);
	colorOrange = QColor(222, 147, 95);
	colorYellow = QColor(240, 198, 116);
	colorGreen = QColor(181, 189, 104);
	colorLBlue = QColor(138, 190, 183);
	colorDBlue = QColor(129, 162, 190);
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
	timeList.prepend(qrand() % 1000);

	if (timeList.size() > 1000)
	{
		timeList.removeLast();
	}

	update(rect());
}

void ChartWidget::paintEvent(QPaintEvent*)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);

	int f = 0;
	for (int i = 0; i < 5 && i < timeList.size(); ++i)
	{
		f += timeList[i];
	}

	f = (timeList.size() < 5 && timeList.size() != 0) ? f / timeList.size() : f / 5;

	QString sst(name);
	sst += QString("\n");
	sst += QString::number(f);
	sst += QString("ms");

	painter.setPen(genColor(0, 1000, f));
	painter.setFont(QFont("DroidSansMonoForPowerline", height() / 3));

	QRect trc;
	painter.drawText(QRect(10, 0, width(), height()), Qt::AlignVCenter, sst, &trc);

	for (int i = 0, x = width() - 1; i < timeList.size() && x > trc.width() + 20; ++i, x -= 11)
	{
		QRectF rc(QPointF(0, 1), QPointF(10.0, (float)height() / 1000.0 * (float)timeList[i]));
		if (rc.height() < 20)
		{
			rc.setHeight(20);
		}
		if (rc.height() > height() - 2)
		{
			rc.setHeight(height() - 2);
		}
		rc.moveBottom(height() - 1);
		rc.moveRight(x);

		painter.fillRect(rc, genColor(0, 1000, timeList[i]));
	}

	painter.drawRect(rect());
}

QColor ChartWidget::genColor(int min, int max, int val)
{
	int cur = 0, step = (max - min) / 5;

	cur += step;
	if (val <= cur)
	{
		return colorDBlue;
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

	cur += step;
	if (val <= cur)
	{
		return colorRed;
	}

	return colorPurple;
}
