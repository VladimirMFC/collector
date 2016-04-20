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

	for (int i = 0; i < 20; ++i)
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
	{
		QMainWindow::keyPressEvent(ke);
	}
}

void MainWindow::initConfigData()
{
	if (Config::keyExist("layout/columns"))
	{
		colCount = Config::getInt("layout/columns");
	}
}
