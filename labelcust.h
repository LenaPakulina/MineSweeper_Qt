#ifndef LABELCUST_H
#define LABELCUST_H

#include <QLabel>
#include <QWidget>

class LabelCust : public QLabel
{
	Q_OBJECT
public:
	explicit LabelCust(QWidget *parent=nullptr);

	// QWidget interface
protected:
	void mousePressEvent(QMouseEvent *event);

signals:
	void sigMousePress();
};

#endif // LABELCUST_H
