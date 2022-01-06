#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QElapsedTimer>
#include <QTimer>

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
	void slotYouWin();
	void slotReduceNumMines();
	void slotTimeTick();
	void slotTimerStart();
	void slotRemoveFlag();

private:
	Ui::MainWindow	*ui;
	QTimer			m_timer;
};
#endif // MAINWINDOW_H
