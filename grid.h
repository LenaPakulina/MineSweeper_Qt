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
	~Grid();

	bool	checkParams();
	void	init();
	void	showEnvironment(Cell* currCell);
	void	setEnabledCells(bool isEnabled);

private:
	QVector<QVector<Cell*>>		m_cells;
	int							m_activeMinesCount;
	QGridLayout					*m_layout;

private:
	void				clear();
	bool				setMine();
	void				setNumbersAboutMines();
	QList<Cell *>		getNeighborsCell(int row, int col, bool applyFilter = false) const;
	bool				checkNeighbor(int row, int col) const;

signals:
	void sigGameOver();
};

#endif // GRID_H
