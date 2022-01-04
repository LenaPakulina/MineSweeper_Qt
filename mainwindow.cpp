#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "grid.h"
#include "diaabout.h"
#include "diasettings.h"
#include "config.h"

#include <QDebug>
#include <QMessageBox>
#include <QPushButton>
#include <QElapsedTimer>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	setWindowTitle(tr("Minesweeper"));

	connect(ui->grid,
			SIGNAL(sigGameOver()),
			SLOT(slotGameOver()));
	connect(ui->lb_status,
			SIGNAL(sigMousePress()),
			SLOT(slotStartAgain()));
	connect(ui->act_AboutProg,
			SIGNAL(triggered(bool)),
			SLOT(slotAboutProgram()));
	connect(ui->act_AboutQt,
			SIGNAL(triggered(bool)),
			SLOT(slotAboutQt()));
	connect(ui->act_settings,
			SIGNAL(triggered(bool)),
			SLOT(slotOpenSettings()));
	connect(ui->act_StartAgain,
			SIGNAL(triggered(bool)),
			SLOT(slotStartAgain()));

	if (g_cfg.m_saveConfig) {
		restoreGeometry(g_cfg.m_windowGeometry);
	}
	slotStartAgain();
}

MainWindow::~MainWindow()
{
	g_cfg.m_windowGeometry = saveGeometry();
	delete ui;
}

void MainWindow::slotGameOver()
{
	ui->lb_status->setPixmap(QPixmap(":/emoji_dead.svg"));
	QMessageBox msgBox;
	msgBox.setWindowTitle(qApp->applicationName());
	msgBox.setText(tr("Game Over!"));
	msgBox.addButton(QMessageBox::Ok);
	QPushButton* pbAgain = msgBox.addButton(tr("Start Again"),
											QMessageBox::ButtonRole::AcceptRole);

	msgBox.exec();
	if (msgBox.clickedButton() == pbAgain) {
		slotStartAgain();
	}
}

void MainWindow::slotStartAgain()
{
	ui->lb_status->setPixmap(QPixmap(":/emoji_happy.svg"));
	ui->grid->init();

	adjustSize(); // update widgets size
	setFixedSize(width(), height());
}

void MainWindow::slotAboutQt()
{
	QMessageBox::aboutQt(this);
}

void MainWindow::slotAboutProgram()
{
	DiaAbout dia(this);
	dia.exec();
}

void MainWindow::slotOpenSettings()
{
	int t_w = g_cfg.m_width;
	int t_h = g_cfg.m_height;
	int t_m = g_cfg.m_mineCount;

	DiaSettings dia(this);
	dia.exec();

	if (t_w != g_cfg.m_width || t_h != g_cfg.m_height || t_m != g_cfg.m_mineCount) {
		slotStartAgain();
	}
}

