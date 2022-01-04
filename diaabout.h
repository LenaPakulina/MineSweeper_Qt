#ifndef DIAABOUT_H
#define DIAABOUT_H

#include <QDialog>

namespace Ui {
class DiaAbout;
}

class DiaAbout : public QDialog
{
	Q_OBJECT

public:
	explicit DiaAbout(QWidget *parent = nullptr);
	~DiaAbout();

private:
	Ui::DiaAbout *ui;
};

#endif // DIAABOUT_H
