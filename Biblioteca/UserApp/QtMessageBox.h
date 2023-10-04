#pragma once

#include <QWidget>
#include "ui_QtMessageBox.h"

class QtMessageBox : public QWidget
{
	Q_OBJECT

public:
	QtMessageBox(QWidget *parent = Q_NULLPTR);
	~QtMessageBox();

	void SetMessage(std::string message);

private slots:
	void on_okBtn_clicked();

private:
	Ui::QtMessageBox ui;
};
