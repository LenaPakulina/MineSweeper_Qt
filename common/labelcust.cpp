#include "labelcust.h"

LabelCust::LabelCust(QWidget *parent) : QLabel(parent)
{
}

void LabelCust::mousePressEvent(QMouseEvent *event)
{
	Q_UNUSED(event);
	emit sigMousePress();
}
