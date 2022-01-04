#include "diasettings.h"
#include "ui_diasettings.h"
#include "config.h"

#include <QUrl>
#include <QFileDialog>
#include <QDesktopServices>

DiaSettings::DiaSettings(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::DiaSettings)
{
	ui->setupUi(this);
	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
	setWindowTitle(tr("Настройки"));

	ui->sb_width->setValue(g_cfg.m_width);
	ui->sb_height->setValue(g_cfg.m_height);
	ui->sb_countMines->setValue(g_cfg.m_mineCount);
	ui->cb_saveSetup->setCheckState(g_cfg.m_saveConfig ? Qt::CheckState::Checked :
														 Qt::CheckState::Unchecked);

	ui->le_pathToConfig->setEnabled(g_cfg.m_saveConfig);
	ui->pb_OpenManager->setEnabled(g_cfg.m_saveConfig);

	int t_i = 0;
	ui->cb_language->addItem(("Русский"), t_i++);
	ui->cb_language->addItem(("English"), t_i++);
	ui->cb_language->setCurrentIndex(g_cfg.m_lastLanguage);

	connect(ui->buttonBox,
			SIGNAL(accepted()),
			SLOT(slotApplySetup()));
	connect(ui->buttonBox,
			SIGNAL(rejected()),
			SLOT(reject()));
	connect(ui->pb_OpenManager,
			SIGNAL(clicked(bool)),
			SLOT(slotOpenFileManager()));

	adjustSize();
}

DiaSettings::~DiaSettings()
{
	delete ui;
}

void DiaSettings::slotApplySetup()
{
	g_cfg.m_width = ui->sb_width->value();
	g_cfg.m_height = ui->sb_height->value();
	g_cfg.m_mineCount = ui->sb_countMines->value();
	g_cfg.m_saveConfig = (ui->cb_saveSetup->checkState() ==
						  Qt::CheckState::Checked) ? true : false;
	g_cfg.m_lastLanguage = ui->cb_language->currentIndex();
}

void DiaSettings::slotOpenFileManager()
{
	const QString& path = QDir::toNativeSeparators(g_cfg.getJsonConfigPath());
	QDesktopServices::openUrl(QUrl::fromLocalFile(path));
}
