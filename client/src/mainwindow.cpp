#include "mainwindow.h"

#include "chartwidget.h"

#include <QtWidgets/QGridLayout>
#include <QtGui/QKeyEvent>

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent), Log(), Config(),
	colCount(1)
{
	initConfigData();

	QWidget *centralWidget = new QWidget(this);
	setCentralWidget(centralWidget);

	QGridLayout *layout = new QGridLayout(centralWidget);

	int chartCount = 25;
	chartCount += chartCount % colCount != 0 ? colCount - (chartCount % colCount) : 0;
	for (int i = 0; i < chartCount; ++i)
	{
		ChartWidget *chart = new ChartWidget(QString("Host") + QString::number(i + 1), centralWidget);
		layout->addWidget(chart, i / colCount, i % colCount);
	}

	centralWidget->setLayout(layout);
}

MainWindow::~MainWindow()
{
}

void MainWindow::keyPressEvent(QKeyEvent* ke)
{
	if (ke->key() == Qt::Key_Escape || ke->key() == Qt::Key_Q)
	{
		ke->accept();
		close();
	}
	else
		QMainWindow::keyPressEvent(ke);
}

void MainWindow::initConfigData()
{
	if (Config::keyExist("window/columns"))
		colCount = Config::getInt("window/columns");
}
