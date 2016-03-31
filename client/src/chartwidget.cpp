#include "chartwidget.h"

#include <QtGui/QPainter>
#include <QtGui/QStaticText>
#include <QtCore/QTimer>
#include <QtCore/QTime>

ChartWidget::ChartWidget(const QString& name, QWidget* parent)
	: QWidget(parent), name(name)
{
	setAutoFillBackground(true);
	QPalette pal = palette();
	pal.setColor(QPalette::Window, QColor(Qt::black));
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

	QString sst(name);
	sst += QString("\n");

	f = (timeList.size() < 5 && timeList.size() != 0) ? f / timeList.size() : f / 5;

	sst += QString::number(f);
	sst += QString("ms");
	f /= 4;

	QColor cl(f, 255 - f, 0);
	painter.setPen(cl);
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

		painter.fillRect(rc, QColor(timeList[i] / 4, 255 - (timeList[i] / 4), 0));
	}

	painter.drawRect(rect());
}
