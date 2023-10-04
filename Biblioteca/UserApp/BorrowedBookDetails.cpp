#include "BorrowedBookDetails.h"
#include "QtMessageBox.h"

BorrowedBookDetails::BorrowedBookDetails(BorrowedBooks borrowedBook, BookDetails bookDetails, QWidget* parent)
	: QWidget(parent),
	borrowedBook(borrowedBook),
	bookDetails(bookDetails)
{
	ui.setupUi(this);
	setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);

	ui.bookAuthor->setText(QString::fromStdString(borrowedBook.getBook().getAuthor()));
	ui.bookISBN->setText(QString::fromStdString(borrowedBook.getBook().getIsbn()));
	ui.bookTitle->setText(QString::fromStdString(borrowedBook.getBook().getTitle()));
	std::string averageRating = std::to_string(bookDetails.GetAverageRating());
	ui.ReturnDate->setText(QString::fromStdString(borrowedBook.getReturningDate()));
	ui.BorrowDate->setText(QString::fromStdString(borrowedBook.getBorrowDate()));
	auto it = std::find(averageRating.begin(), averageRating.end(), '.');
	averageRating.erase(it + 3, averageRating.end());
	ui.bookRating->setText(QString::fromStdString(averageRating + "/5"));
	ui.bookLanguage->setText(QString::fromStdString(bookDetails.GetLanguageCode()));
	ui.bookTags->setText("#" + QString::fromStdString(bookDetails.GetTags().substr(0, 160) + "...").replace(" ", " #"));

	ui.bookTags->setWordWrap(true);
	ui.bookTags->setFixedSize(QSize(269, 81));
	QString imageURL = QString::fromStdString(bookDetails.GetImageUrl());
	if (imageURL.indexOf("https") == 0)
	{
		imageURL.remove(4, 1);
	}
	QNetworkAccessManager* nam = new QNetworkAccessManager(this);
	connect(nam, &QNetworkAccessManager::finished, this, &BorrowedBookDetails::loadImage);

	QUrl imageNoSecureURL = imageURL;
	QNetworkRequest request(imageNoSecureURL);
	nam->get(request);

	setAttribute(Qt::WA_DeleteOnClose);

}

BorrowedBookDetails::~BorrowedBookDetails()
{
}

void BorrowedBookDetails::on_returnBook_clicked()
{
	user.SetBookId(std::stoi(borrowedBook.getBook().getBookId()));
	user.SetOption(returnBook);

	QtMessageBox* warningMessage = new QtMessageBox;
	warningMessage->SetMessage("The book has been returned!");
	warningMessage->show();
}

void BorrowedBookDetails::on_prolongBDate_clicked()
{
	if (user.CheckMaxProlongedDate(borrowedBook))
	{
		user.SetBookId(std::stoi(borrowedBook.getBook().getBookId()));
		user.SetOption(prolongBorrowDate);
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		for (auto& i : user.GetBorrowedBooks())
			if (i.getBook().getBookId() == borrowedBook.getBook().getBookId())
			{
				borrowedBook.setReturningDate(i.getReturningDate());
				ui.ReturnDate->setText(QString::fromStdString(borrowedBook.getReturningDate()));

				QtMessageBox* warningMessage = new QtMessageBox;
				warningMessage->SetMessage("Return date has been prolonged!");
				warningMessage->show();
			}
	}
	else
	{
		QtMessageBox* warningMessage = new QtMessageBox;
		warningMessage->SetMessage("You can't prolong the borrow date \nmore than 2 times!");
		warningMessage->show();
	}
}

void BorrowedBookDetails::loadImage(QNetworkReply* reply)
{
	QPixmap bookCoverImage;
	bookCoverImage.loadFromData(reply->readAll());
	ui.bookImage->setPixmap(bookCoverImage);

	int w = ui.bookImage->width();
	int h = ui.bookImage->height();

	ui.bookImage->setPixmap(bookCoverImage.scaled(w, h, Qt::KeepAspectRatio));

}
