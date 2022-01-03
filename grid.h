#ifndef GRID_H
#define GRID_H

#include <QWidget>
#include <QVector>
#include <QGridLayout>

class Cell;

class Grid : public QWidget
{
	Q_OBJECT
public:
	explicit Grid(QWidget *parent = nullptr);
	bool	checkParams();
	void	init();

private:
	QVector<QVector<Cell*>>		m_cells;
	int							m_activeMinesCount;
	QGridLayout					*m_layout;

private:
	void	clear();
	bool	setMine();

signals:
	void sigGameOver();
};

#endif // GRID_H
