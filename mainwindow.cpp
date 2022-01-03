#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "grid.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	setWindowTitle(tr("Minesweeper"));

	m_grig = new Grid(this);
	connect(m_grig,
			SIGNAL(sigGameOver()),
			SLOT(slotGameOver()));
	setCentralWidget(m_grig);

	adjustSize(); // update widgets size
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::slotGameOver()
{
	QMessageBox msgBox;
	msgBox.setWindowTitle(qApp->applicationName());
	msgBox.setText(tr("Game Over!"));
	msgBox.addButton(QMessageBox::Ok);
	msgBox.addButton(tr("Start Again"), QMessageBox::ButtonRole::AcceptRole);

	msgBox.exec();
}

