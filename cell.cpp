#include "cell.h"
#include "grid.h"

#include <QDebug>
#include <QMouseEvent>

#define SIDE_SIZE 30

Cell::Cell(Grid* mainGrid)
	: QPushButton(mainGrid),
	m_mainGrid(mainGrid)
{
	setMinimumHeight(SIDE_SIZE);
	setMaximumHeight(SIDE_SIZE);
	setMinimumWidth(SIDE_SIZE);
	setMaximumWidth(SIDE_SIZE);

	m_publicState = CELL_STATE::FREE;
	m_privateState = CELL_STATE::FREE;
}

void Cell::setPrivateState(const CELL_STATE &state)
{
	m_privateState = state;
	setState(m_privateState);
}

void Cell::setPublicState(const CELL_STATE &state)
{
	m_publicState = state;
	setState(m_publicState);
}

void Cell::setState(CELL_STATE& state)
{
	switch (state) {
	case CELL_STATE::FREE:
		setText("F");
		break;
	case CELL_STATE::MINE:
		setText("M");
		break;
	case CELL_STATE::FLAG:
		setText("G");
		break;
	case CELL_STATE::QUESTIONS:
		setText("Q");
		break;
	default:
		break;
	};
}

CELL_STATE Cell::getPrivateState() const
{
	return m_privateState;
}

CELL_STATE Cell::getPublicState() const
{
	return m_publicState;
}

void Cell::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::MouseButton::RightButton) {
		if (m_publicState == CELL_STATE::FREE) {
			setPublicState(CELL_STATE::FLAG);
		} else if (m_publicState == CELL_STATE::FLAG) {
			setPublicState(CELL_STATE::QUESTIONS);
		} else if (m_publicState == CELL_STATE::QUESTIONS) {
			setPublicState(CELL_STATE::FREE);
		}
	} else if (event->button() == Qt::MouseButton::LeftButton) {
		if (m_privateState == CELL_STATE::FREE) {
			// доделать
		} else if (m_publicState == CELL_STATE::MINE) {
			if (m_mainGrid) {
				emit m_mainGrid->sigGameOver();
			}
		}
	}
}
