#ifndef CELL_H
#define CELL_H

#include <QPushButton>

class Grid;
enum class CELL_STATE{
	FREE = 0,
	MINE,
	FLAG,
	QUESTIONS,
	UNKNOWN
};

class Cell : public QPushButton
{
	Q_OBJECT
public:
	explicit Cell(Grid* parent = nullptr);
	~Cell();

	void			setPrivateState(const CELL_STATE& state);
	void			setPublicState(const CELL_STATE& state);
	CELL_STATE		getPrivateState() const;
	CELL_STATE		getPublicState() const;
	void			addMine();
	void			setNumMine();
	int				getNumMine() const;
	bool			isUncovered();

private:
	void setState(CELL_STATE& state);

private:
	CELL_STATE		m_publicState;
	CELL_STATE		m_privateState;
	Grid			*m_mainGrid;
	int				m_numMines;
	bool			m_isUncovered;

	// QWidget interface
protected:
	void mousePressEvent(QMouseEvent *event);
};

#endif // CELL_H
