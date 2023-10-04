#include "SearchBook.h"
#include "Login.h"
#include "QtMessageBox.h"
#include "SelectedBookDetails.h"

SearchBook::SearchBook(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.listWidget->setViewMode(QListWidget::IconMode);
	ui.listWidget->setIconSize(QSize(200, 150));
	ui.listWidget->setResizeMode(QListWidget::Adjust);
	ui.listWidget->setSpacing(30);
	nam = new QNetworkAccessManager(this);
	connect(nam, &QNetworkAccessManager::finished, this, &SearchBook::loadImage);
	connect(ui.listWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)),
		this, SLOT(onBookListItemDoubleClicked(QListWidgetItem*)));
	setAttribute(Qt::WA_DeleteOnClose);
}

void SearchBook::on_searchBtn_clicked()
{
	ui.listWidget->blockSignals(true);
	ui.listWidget->clear();
	ui.listWidget->blockSignals(false);
	std::string searchInput = ui.searchInput->text().toStdString();

	if (searchInput.size())
	{
		std::for_each(searchInput.begin(), searchInput.end(), [](char& character) {
			character  = ::tolower(character);
			});
		user.SetKeyword(searchInput);
		user.SetOption(searchBook);
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		std::vector<Book> searchResult = user.GetSearchedBooks();
		
		if (searchResult.size())
		{
			requests.clear();
			titleAndAuthor.clear();
			for (int i=0;i<searchResult.size();i++)
			{
				QString imageURL = QString::fromStdString(searchResult[i].getImgUrl());

				if (imageURL.indexOf("https") == 0)
				{
					imageURL.remove(4, 1);
				}
				titleAndAuthor.push_back(QString(QString::fromStdString(searchResult[i].getTitle() + " - " + searchResult[i].getAuthor())));
				QUrl imageNoSecureURL = imageURL;
				QNetworkRequest request(imageNoSecureURL);
				requests.insert(nam->get(request), i);
			}
		}
		else
		{
			QtMessageBox* warningMessage = new QtMessageBox;
			warningMessage->SetMessage("No matches found!");
			warningMessage->show();
		}
	}
	else
	{
		QtMessageBox* warningMessage = new QtMessageBox;
		warningMessage->SetMessage("No search input given!");
		warningMessage->show();
	}
}

void SearchBook::loadImage(QNetworkReply* reply)
{
	QPixmap bookCoverImage;
	bookCoverImage.loadFromData(reply->readAll());
	QListWidgetItem* item = new QListWidgetItem(bookCoverImage,titleAndAuthor[requests[reply]]);
	item->setSizeHint(QSize(100, 150));
	//item->setBackgroundColor(QColor(251, 206, 79));
	ui.listWidget->addItem(item);
	reply->deleteLater();
}


void SearchBook::onBookListItemDoubleClicked(QListWidgetItem* item)
{
	std::vector<Book> searchResult = user.GetSearchedBooks();
	int i;
	for (i = 0; i < searchResult.size(); i++)
	{
		if (item->text().toStdString() == std::string(searchResult[i].getTitle() + " " + "-" + " " + searchResult[i].getAuthor()))
		{
			user.SetBookId(std::stoi(searchResult[i].getBookId()));
			break;
		}
	}
	user.SetOption(bookDetails);
	std::this_thread::sleep_for(std::chrono::milliseconds(700));
	BookDetails currentBook = user.GetBookDetails();
	SelectedBookDetails* bookDetails = new SelectedBookDetails(searchResult[i], currentBook);
	bookDetails->show();
}

SearchBook::~SearchBook()
{
	delete nam;
}

std::string SearchBook::GetSearchInput()
{
	return userSearchInput;
}
