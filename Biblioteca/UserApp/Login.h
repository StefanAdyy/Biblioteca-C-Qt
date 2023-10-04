#pragma once

#include <QWidget>
#include "ui_Login.h"
#include "SearchBook.h"

class Login : public QWidget
{
	Q_OBJECT

public:
	Login(QWidget* parent = Q_NULLPTR);
	~Login();

private slots:
	void on_registerBtn_clicked();
	void on_loginBtn_clicked();

private:
	Ui::Login ui;
};
