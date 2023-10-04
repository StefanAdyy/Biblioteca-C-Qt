#pragma once

#include <QWidget>
#include "ui_BorrowedBooksList.h"
#include <QtNetwork/qnetworkaccessmanager.h>
#include <QtNetwork/qnetworkreply.h>
#include <qimagereader.h>
#include "Login.h"
#include "Book.h"
#include "QtMessageBox.h"
#include "BorrowedBookDetails.h"
#include "BookDetails.h"

class BorrowedBooksList : public QWidget
{
	Q_OBJECT

public:
	BorrowedBooksList(QWidget *parent = Q_NULLPTR);
	~BorrowedBooksList();
	void loadBooks();

private slots:
	void onBorrowedBookListItemDoubleClicked(QListWidgetItem* item);
	void loadImage(QNetworkReply* reply);
	void on_changePasswordBtn_clicked();
	void on_refreshBtn_clicked();

private:
	QNetworkAccessManager* nam;
	Ui::BorrowedBooksList ui;
	std::vector<QString> titleAndAuthor;
	QMap<QNetworkReply*, int> requests;
};
