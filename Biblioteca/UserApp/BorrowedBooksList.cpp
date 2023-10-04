#include "BorrowedBooksList.h"
#include "PasswordChange.h"

BorrowedBooksList::BorrowedBooksList(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.borrowedBooksList->setViewMode(QListWidget::IconMode);
	ui.borrowedBooksList->setIconSize(QSize(200, 150));
	ui.borrowedBooksList->setResizeMode(QListWidget::Adjust);
	ui.borrowedBooksList->setSpacing(30);

	setAttribute(Qt::WA_DeleteOnClose);
	nam = new QNetworkAccessManager(this);
	connect(nam, &QNetworkAccessManager::finished, this, &BorrowedBooksList::loadImage);

	connect(ui.borrowedBooksList, SIGNAL(itemDoubleClicked(QListWidgetItem*)),
		this, SLOT(onBorrowedBookListItemDoubleClicked(QListWidgetItem*)));

}

void BorrowedBooksList::loadImage(QNetworkReply* reply)
{
	QPixmap bookCoverImage;
	bookCoverImage.loadFromData(reply->readAll());
	QListWidgetItem* item = new QListWidgetItem(bookCoverImage, titleAndAuthor[requests[reply]]);
	item->setSizeHint(QSize(100, 150));
	ui.borrowedBooksList->addItem(item);
	reply->deleteLater();
}

void BorrowedBooksList::on_changePasswordBtn_clicked()
{
	PasswordChange* passwordChange = new PasswordChange;
	passwordChange->show();
}

void BorrowedBooksList::on_refreshBtn_clicked()
{
	loadBooks();
}

void BorrowedBooksList::onBorrowedBookListItemDoubleClicked(QListWidgetItem* item)
{
	std::vector<BorrowedBooks> borrowedBooks = user.GetBorrowedBooks();
	int i;
	for (i = 0; i < borrowedBooks.size(); i++)
	{
		if (item->text().toStdString() == std::string(borrowedBooks[i].getBook().getTitle() + " " + "-" + " " + borrowedBooks[i].getBook().getAuthor()))
		{
			user.SetBookId(std::stoi(borrowedBooks[i].getBook().getBookId()));
			break;
		}
	}
	user.SetOption(bookDetails);
	std::this_thread::sleep_for(std::chrono::milliseconds(700));
	BookDetails currentBook = user.GetBookDetails();
	BorrowedBookDetails* bookDetails = new BorrowedBookDetails(borrowedBooks[i], currentBook);
	bookDetails->show();
}

BorrowedBooksList::~BorrowedBooksList()
{
	delete nam;
}

void BorrowedBooksList::loadBooks()
{
	ui.borrowedBooksList->blockSignals(true);
	ui.borrowedBooksList->clear();
	ui.borrowedBooksList->blockSignals(false);
	std::vector<BorrowedBooks> borrowedBooks = user.GetBorrowedBooks(); //= send input to server and receive a vector (of books) containing all the books matching the search input
	titleAndAuthor.clear();
	requests.clear();
	if (borrowedBooks.size())
	{
		Book borrowedBook;
		for (int i=0;i< borrowedBooks.size();i++)
		{
			borrowedBook = borrowedBooks[i].getBook();
			QString imageURL = QString::fromStdString(borrowedBook.getImgUrl());

			if (imageURL.indexOf("https") == 0)
			{
				imageURL.remove(4, 1);
			}
			titleAndAuthor.push_back(QString::fromStdString(borrowedBook.getTitle() + " - " + borrowedBook.getAuthor()));

			QUrl imageNoSecureURL = imageURL;
			QNetworkRequest request(imageNoSecureURL);
			requests.insert(nam->get(request), i);
		}
	}
	else
		if (user.GetLoginStatus())
		{
			QtMessageBox* warningMessage = new QtMessageBox;
			warningMessage->SetMessage("No borrowed books found!");
			warningMessage->show();
		}
}
