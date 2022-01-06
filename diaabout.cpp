#include "diaabout.h"
#include "ui_diaabout.h"

DiaAbout::DiaAbout(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::DiaAbout)
{
	ui->setupUi(this);
	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
	setWindowTitle(tr("О программе"));
	ui->tb_info->setReadOnly(true);

	QString msg = QString("<html>"
					 "<b>%1</b> - %2<br><br>"
					 "<b>%3: </b> 1 <br>"
					 "<b>%4: </b>"
					 "<a href=\"https://github.com/LenaPakulina/MineSweeper_Qt\">https://github.com/LenaPakulina/MineSweeper_Qt</a><br><br>"
					 "<b>%5: </b> krissini@mail.ru <br><br>"
					 "<b>%6: </b>"
					 "<ul>"
					 "<li>%7 <a href=\"http://tango.freedesktop.org/Tango_Icon_Library\">Tango</a> </li>"
					 "<li>%7 <a href=\"http://www.fatcow.com/free-icons\">FatCow</a></li>"
					 "</ul>"
					 "</html>").arg(qApp->applicationName(),
									tr("Компьютерная игра-головоломка."),
									tr("Версия"),
									tr("По вопросам"),
									tr("Почта"),
									tr("В программе использованы"),
									tr("иконки"));
	ui->tb_info->setText(msg);
}

DiaAbout::~DiaAbout()
{
	delete ui;
}
