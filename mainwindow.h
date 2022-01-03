#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

private:
	Ui::MainWindow	*ui;
	Grid			*m_grig;
};
#endif // MAINWINDOW_H
