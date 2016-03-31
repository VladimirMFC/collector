#include "mainwindow.h"

#include "chartwidget.h"

#include <QtWidgets/QVBoxLayout>
#include <QtGui/QKeyEvent>

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent)
{
	QWidget *centralWidget = new QWidget(this);
	setCentralWidget(centralWidget);

	QVBoxLayout *layout = new QVBoxLayout;

	for (int i = 0; i < 10; ++i)
	{
		ChartWidget *chart = new ChartWidget("Host");
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
