#include "grid.h"
#include "config.h"
#include "cell.h"

#include <QSet>
#include <QDebug>
#include <QRandomGenerator>
#include <QGridLayout>

Grid::Grid(QWidget *parent) : QWidget(parent)
{
	m_activeMinesCount = 0;
	m_activeFreeCount = 0;
	m_layout = new QGridLayout(this);
	m_layout->setSpacing(1);
	m_layout->setMargin(0);
}

Grid::~Grid()
{
	if (m_layout) {
		m_layout->deleteLater();
	}
	clear();
}

bool Grid::checkParams()
{
	// проверить введенные параметры на адекватность
	return true;
}

void Grid::init()
{
	clear();
	m_activeMinesCount = 0;

	// initial grid creation
	m_cells.reserve(g_cfg.m_height);
	for (int i = 0; i < g_cfg.m_height; i++) {
		QVector<Cell*> t_row;
		t_row.reserve(g_cfg.m_width);
		for (int j = 0; j < g_cfg.m_width; j++) {
			t_row.append(new Cell(this));
		}
		m_cells.append(t_row);
	}

	// Filling in the grid
	while(m_activeMinesCount != g_cfg.m_mineCount) {
		while(!setMine()) {
			// nothing ToDo
		}
	}

	// filling Layout
	for (int i = 0; i < g_cfg.m_height; i++) {
		for (int j = 0; j < g_cfg.m_width; j++) {
			m_layout->addWidget(m_cells.at(i).at(j), i, j);
		}
	}

	// Determine the number of Mines
	setNumbersAboutMines();

	m_activeFreeCount = g_cfg.m_width * g_cfg.m_width;
}

void Grid::showEnvironment(Cell *currCell)
{
	QList<Cell*> neighbors;
	for (int i = 0; i < g_cfg.m_height; i++) {
		for (int j = 0; j < g_cfg.m_width; j++) {
			Cell* cell = m_cells.at(i).at(j);
			if (cell != currCell) {
				continue;
			}
			const int numMines = cell->getNumMine();
			if (numMines == 0) {
				neighbors = getNeighborsCell(i, j,true);
				for (Cell* neighbor: neighbors) {
					neighbor->setNumMine();
					showEnvironment(neighbor);
				}
			}
			cell->setNumMine();
		}
	}
}

void Grid::setEnabledCells(bool isEnabled)
{
	for (int i = 0; i < g_cfg.m_height; i++) {
		for (int j = 0; j < g_cfg.m_width; j++) {
			Cell* cell = m_cells.at(i).at(j);
			cell->setEnabled(isEnabled);
			if (cell->getPrivateState() == CELL_STATE::MINE) {
				cell->setPublicState(cell->getPrivateState());
			}
		}
	}
}

void Grid::reduceFreeCells()
{
	m_activeFreeCount--;
	if (m_activeFreeCount == g_cfg.m_mineCount) {
		emit sigYouWin();
	}
}

void Grid::clear()
{
	for (QVector<Cell*>& row: m_cells) {
		for (Cell* cell: row) {
			cell->deleteLater();
		}
	}
	m_cells.clear();
}

bool Grid::setMine()
{
	const int h = QRandomGenerator::global()->bounded(0, g_cfg.m_height);
	const int w = QRandomGenerator::global()->bounded(0, g_cfg.m_width);

	Cell *t_cell = m_cells.at(h).at(w);
	if (t_cell->getPrivateState() == CELL_STATE::MINE) {
		return false;
	} else {
		t_cell->setPrivateState(CELL_STATE::MINE);
		m_activeMinesCount++;
	}

	return true;
}

void Grid::setNumbersAboutMines()
{
	for (int i = 0; i < g_cfg.m_height; i++) {
		for (int j = 0; j < g_cfg.m_width; j++) {
			Cell* cell = m_cells.at(i).at(j);
			if (cell->getPrivateState() != CELL_STATE::MINE) {
				continue;
			}
			const QList<Cell*>& neighbors = getNeighborsCell(i, j);

			for (Cell* cell: neighbors) {
				if (cell->getPrivateState() == CELL_STATE::FREE) {
					cell->addMine();
				}
			}
		}
	}
}

QList<Cell*> Grid::getNeighborsCell(int row, int col, bool applyFilter) const
{
	QList<Cell*> cells;
	if (row < 0 || col < 0 || row >= g_cfg.m_height || col >= g_cfg.m_width) {
		qDebug() << tr("Код ошибки: 002. Ошибки поиска соседей ячейки");
		return cells;
	}

	if (checkNeighbor(row-1, col-1)) cells << m_cells.at(row-1).at(col-1);
	if (checkNeighbor(row-1, col)) cells << m_cells.at(row-1).at(col);
	if (checkNeighbor(row-1, col+1)) cells << m_cells.at(row-1).at(col+1);
	if (checkNeighbor(row, col+1)) cells << m_cells.at(row).at(col+1);
	if (checkNeighbor(row+1, col+1)) cells << m_cells.at(row+1).at(col+1);
	if (checkNeighbor(row+1, col)) cells << m_cells.at(row+1).at(col);
	if (checkNeighbor(row+1, col-1)) cells << m_cells.at(row+1).at(col-1);
	if (checkNeighbor(row, col-1)) cells << m_cells.at(row).at(col-1);

	if (applyFilter) {
		for (Cell* cell: cells) {
			if (cell->isUncovered()) {
				cells.removeOne(cell);
			}
		}
	}

	return cells;
}

bool Grid::checkNeighbor(int row, int col) const
{
	if (row < 0 || col < 0 || row >= g_cfg.m_height || col >= g_cfg.m_width) {
		return false;
	}

	return true;
}
