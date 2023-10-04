#pragma once

#include <QWidget>
#include "ui_BorrowedBookDetails.h"
#include <QtNetwork/qnetworkreply.h>
#include "BorrowedBooks.h"
#include "BookDetails.h"
#include "User.h"

class BorrowedBookDetails : public QWidget
{
	Q_OBJECT

public:
	BorrowedBookDetails(BorrowedBooks borrowedBook, BookDetails bookDetails, QWidget* parent = Q_NULLPTR);
	~BorrowedBookDetails();

private slots:
	void loadImage(QNetworkReply* reply);
	void on_returnBook_clicked();
	void on_prolongBDate_clicked();

private:
	BorrowedBooks borrowedBook;
	BookDetails bookDetails;
	Ui::BorrowedBookDetails ui;
};
