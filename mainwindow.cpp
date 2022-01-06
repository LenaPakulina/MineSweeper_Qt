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
	setWindowTitle(tr("Сапёр"));

	connect(ui->grid,
			SIGNAL(sigGameOver()),
			SLOT(slotGameOver()));
	connect(ui->grid,
			SIGNAL(sigYouWin()),
			SLOT(slotYouWin()));
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
	connect(ui->grid,
			SIGNAL(sigInstallFlag()),
			SLOT(slotReduceNumMines()));
	connect(ui->grid,
			SIGNAL(sigRemoveFlag()),
			SLOT(slotRemoveFlag()));
	connect(&m_timer,
			SIGNAL(timeout()),
			SLOT(slotTimeTick()));

	if (g_cfg.m_saveConfig) {
		restoreGeometry(g_cfg.m_windowGeometry);
	}
	slotStartAgain();
}

MainWindow::~MainWindow()
{
	g_cfg.m_windowGeometry = saveGeometry();
	g_cfg.save();
	delete ui;
}

void MainWindow::slotGameOver()
{
	m_timer.stop();
	ui->lb_status->setPixmap(QPixmap(":/emoji_dead.svg"));
	QMessageBox msgBox;
	msgBox.setWindowTitle(qApp->applicationName());
	msgBox.setText(tr("Вы не выиграли!"));
	msgBox.addButton(QMessageBox::Ok);
	QPushButton* pbAgain = msgBox.addButton(tr("Начать новую"),
											QMessageBox::ButtonRole::AcceptRole);

	msgBox.exec();
	if (msgBox.clickedButton() == pbAgain) {
		slotStartAgain();
	}
}

void MainWindow::slotStartAgain()
{
	m_timer.stop();
	ui->lcdNum_Time->display(0);
	ui->lb_status->setPixmap(QPixmap(":/emoji_happy.svg"));
	ui->grid->init();

	adjustSize(); // update widgets size
	setFixedSize(width(), height());
	ui->lcdNum_MineCount->display(g_cfg.m_mineCount);

	connect(ui->grid,
			SIGNAL(sigPressedToCell()),
			SLOT(slotTimerStart()));
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
	int t_lastLanguage = g_cfg.m_lastLanguage;

	DiaSettings dia(this);
	dia.exec();

	if (t_w != g_cfg.m_width || t_h != g_cfg.m_height || t_m != g_cfg.m_mineCount) {
		slotStartAgain();
	}
	if (t_lastLanguage != g_cfg.m_lastLanguage) {
		ui->retranslateUi(this);
	}
}

void MainWindow::slotYouWin()
{
	m_timer.stop();
	ui->grid->setEnabledCells(false);
	ui->lb_status->setPixmap(QPixmap(":/emoji_shocked.svg"));
	QMessageBox msgBox;
	msgBox.setWindowTitle(qApp->applicationName());
	msgBox.setText(tr("Вы выиграли!"));
	msgBox.addButton(QMessageBox::Ok);
	QPushButton* pbAgain = msgBox.addButton(tr("Начать новую"),
											QMessageBox::ButtonRole::AcceptRole);

	msgBox.exec();
	if (msgBox.clickedButton() == pbAgain) {
		slotStartAgain();
	}
}

void MainWindow::slotReduceNumMines()
{
	const int tempValue = ui->lcdNum_MineCount->intValue();
	if (tempValue > 0) {
		ui->lcdNum_MineCount->display(tempValue-1);
	}
}

void MainWindow::slotTimeTick()
{
	ui->lcdNum_Time->display(ui->lcdNum_Time->intValue()+1);
}

void MainWindow::slotTimerStart()
{
	m_timer.start(1000);
	disconnect(ui->grid,
			   SIGNAL(sigPressedToCell()),
			   this,
			   SLOT(slotTimerStart()));
}

void MainWindow::slotRemoveFlag()
{
	const int tempValue = ui->lcdNum_MineCount->intValue();
	ui->lcdNum_MineCount->display(tempValue+1);
}
