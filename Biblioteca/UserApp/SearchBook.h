#pragma once

#include <QWidget>
#include "ui_SearchBook.h"
#include <QtNetwork/qnetworkaccessmanager.h>
#include <QtNetwork/qnetworkreply.h>
#include <qimagereader.h>
#include "User.h"
extern User user;
class SearchBook : public QWidget
{
	Q_OBJECT

public:
	SearchBook(QWidget* parent = Q_NULLPTR);
	~SearchBook();
	std::string GetSearchInput();

private slots:
	void on_searchBtn_clicked();
	void loadImage(QNetworkReply* reply);
	void onBookListItemDoubleClicked(QListWidgetItem* item);

private:
	std::string userSearchInput;
	Ui::SearchBook ui;
	std::vector<QString> titleAndAuthor;
	QNetworkAccessManager* nam;
	QMap<QNetworkReply*, int> requests;
};
