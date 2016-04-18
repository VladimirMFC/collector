#include "mainwindow.h"

#include "chartwidget.h"

#include <QtWidgets/QGridLayout>
#include <QtGui/QKeyEvent>

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent), Log(), Config()
{
	QWidget *centralWidget = new QWidget(this);
	setCentralWidget(centralWidget);

	QGridLayout *layout = new QGridLayout(centralWidget);

	for (int i = 0; i < 10; ++i)
	{
		ChartWidget *chart = new ChartWidget(QString("Host") + QString::number(i + 1), centralWidget);
		layout->addWidget(chart);
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
