#pragma once

#include <QWidget>
#include "ui_PasswordChange.h"

class PasswordChange : public QWidget
{
	Q_OBJECT

public:
	PasswordChange(QWidget *parent = Q_NULLPTR);
	~PasswordChange();
	
private slots:
	void on_passwordChangeBtn_clicked();

private:
	Ui::PasswordChange ui;
};
