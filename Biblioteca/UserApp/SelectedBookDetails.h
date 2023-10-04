#pragma once

#include <QWidget>
#include "ui_SelectedBookDetails.h"
#include <QtNetwork/qnetworkaccessmanager.h>
#include <QtNetwork/qnetworkreply.h>
#include <qimagereader.h>
#include "Book.h"
#include "BookDetails.h"
class SelectedBookDetails : public QWidget
{
	Q_OBJECT

public:
	SelectedBookDetails(Book book,BookDetails bookDetails,QWidget *parent = Q_NULLPTR);
	~SelectedBookDetails();

private slots:
	void loadImage(QNetworkReply* reply);
	void on_borrowBtn_clicked();

private:
	Book book;
	BookDetails bookDetails;
	Ui::SelectedBookDetails ui;
};
