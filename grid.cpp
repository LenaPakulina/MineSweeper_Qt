#include "grid.h"
#include "config.h"
#include "cell.h"
#include "randomizer.h"

#include <QRandomGenerator>

Grid::Grid(QWidget *parent) : QWidget(parent)
{
	m_activeMinesCount = 0;
	m_layout = new QGridLayout(this);
	init();
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
			m_layout->addWidget(m_cells.at(j).at(i), i, j);
		}
	}
}

void Grid::clear()
{
	for (QVector<Cell*>& row: m_cells) {
		qDeleteAll(row);
	}
	m_cells.clear();
}

bool Grid::setMine()
{
	const int h = QRandomGenerator::global()->bounded(0, g_cfg.m_height - 1);
	const int w = QRandomGenerator::global()->bounded(0, g_cfg.m_width - 1);

	Cell *t_cell = m_cells.at(h).at(w);
	if (t_cell->getPrivateState() == CELL_STATE::MINE) {
		return false;
	} else {
		t_cell->setPrivateState(CELL_STATE::MINE);
		m_activeMinesCount++;
	}

	return true;
}
