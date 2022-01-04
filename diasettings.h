#ifndef DIASETTINGS_H
#define DIASETTINGS_H

#include <QDialog>

namespace Ui {
class DiaSettings;
}

class DiaSettings : public QDialog
{
	Q_OBJECT

public:
	explicit DiaSettings(QWidget *parent = nullptr);
	~DiaSettings();

private:
	Ui::DiaSettings *ui;

private slots:
	void slotApplySetup();
	void slotOpenFileManager();
};

#endif // DIASETTINGS_H
