#include "common/mainwindow.h"
#include "common/config.h"

#include <QDebug>
#include <QFile>
#include <QDir>
#include <QApplication>
#include <QTranslator>
#include <QLibraryInfo>

int main(int argc, char *argv[])
{
	QCoreApplication::setOrganizationName("Pakulina");
	QCoreApplication::setOrganizationDomain("krissini@mail.ru");
	QCoreApplication::setApplicationName("MineSweeper");

	QApplication a(argc, argv);
	g_cfg.load();

	// копирование файла перевода
	QString proDir = PRO_RJ_PATH;
	if (!QFile::copy(proDir + QDir::separator() + "MineSweeper_en.qm",
				qApp->applicationDirPath() + QDir::separator() +  + "MineSweeper_en.qm")) {
		qDebug() << "Не удалось копировать файл перевода";
	}

	MainWindow w;
	w.show();
	return a.exec();
}
