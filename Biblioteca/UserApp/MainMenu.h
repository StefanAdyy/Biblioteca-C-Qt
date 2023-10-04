#pragma once

#include <QWidget>
#include "ui_MainMenu.h"

class MainMenu : public QWidget
{
	Q_OBJECT

public:
	MainMenu(QWidget *parent = Q_NULLPTR);
	~MainMenu();

public slots:
	void DeleteUserLogout();

private slots:
	void on_loginBtn_clicked();
	void on_logOutBtn_clicked();
	void on_deleteUserBtn_clicked();
signals:
	void on_yesBtn_clicked();
private:
	Ui::MainMenu ui;
	int lastIndex;
};
