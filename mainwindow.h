#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QElapsedTimer>

QT_BEGIN_NAMESPACE
namespace Ui {
	class MainWindow;
}
QT_END_NAMESPACE

class Grid;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

public slots:
	void slotGameOver();
	void slotStartAgain();
	void slotAboutQt();
	void slotAboutProgram();
	void slotOpenSettings();

private:
	Ui::MainWindow	*ui;
};
#endif // MAINWINDOW_H
