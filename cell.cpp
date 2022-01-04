#include "cell.h"
#include "grid.h"

#include <QImage>
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

	m_isUncovered = false;
	m_numMines = 0;
	m_publicState = CELL_STATE::FREE;
	setPrivateState(CELL_STATE::FREE);
	setEnabled(true);
}

Cell::~Cell()
{
	//qDebug() << "~Cell";
}

void Cell::setPrivateState(const CELL_STATE &state)
{
	m_privateState = state;
	switch (m_privateState) {
	case CELL_STATE::FREE:
		setStyleSheet("background-color: rgb(220, 220, 220);");
		break;
	case CELL_STATE::MINE:
		setStyleSheet("background-color: rgb(210, 210, 210);");
		break;
	default:
		break;
	};
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
		setIcon(QIcon());
		break;
	case CELL_STATE::MINE:
		setIcon(QIcon(":/mine.svg"));
		break;
	case CELL_STATE::FLAG:
		setIcon(QIcon(":/flag.svg"));
		break;
	case CELL_STATE::QUESTIONS:
		setIcon(QIcon(":/question.svg"));
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

void Cell::addMine()
{
	m_numMines++;
}

void Cell::setNumMine()
{
	m_isUncovered = true;
	setStyleSheet("border: 1px solid #8f8f91;");
	if (m_numMines == 0) {
		setEnabled(false);
		return;
	}
	setText(QString::number(m_numMines));
}

int Cell::getNumMine() const
{
	return m_numMines;
}

bool Cell::isUncovered()
{
	return m_isUncovered;
}

void Cell::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::MouseButton::RightButton) {
		if (m_isUncovered) {
			return;
		}
		if (m_publicState == CELL_STATE::FREE) {
			setPublicState(CELL_STATE::FLAG);
		} else if (m_publicState == CELL_STATE::FLAG) {
			setPublicState(CELL_STATE::QUESTIONS);
		} else if (m_publicState == CELL_STATE::QUESTIONS) {
			setPublicState(CELL_STATE::FREE);
		}
	} else if (event->button() == Qt::MouseButton::LeftButton) {
		if (m_privateState == CELL_STATE::FREE) {
			if (m_mainGrid) {
				m_mainGrid->showEnvironment(this);
			}
		} else if (m_privateState == CELL_STATE::MINE) {
			if (m_mainGrid) {
				m_mainGrid->setEnabledCells(false);
				emit m_mainGrid->sigGameOver();
			}
		} else {
			qDebug() << tr("Код ошибки: 001. Неопределенное поведение");
		}
	}
}
