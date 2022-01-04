#include "mainwindow.h"
#include "config.h"

#include <QApplication>

int main(int argc, char *argv[])
{
	QCoreApplication::setOrganizationName("Pakulina");
	QCoreApplication::setOrganizationDomain("krissini@mail.ru");
	QCoreApplication::setApplicationName("MineSweeper");

	QApplication a(argc, argv);
	g_cfg.load();

	MainWindow w;
	w.show();
	return a.exec();
}
