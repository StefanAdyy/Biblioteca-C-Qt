#include "Book.h"

Book::Book(const std::string& id, const std::string& title, const std::string& auth, const std::string& ISBNcode, const std::string& imgURL):
	bookId(id),
	originalTitle(title),
	author(auth),
	isbn(ISBNcode),
	imageUrl(imgURL)
{
}

Book::Book(const Book& book)
{
	this->author = book.author;
	this->bookId = book.bookId;
	this->isbn = book.isbn;
	this->originalTitle = book.originalTitle;
	this->imageUrl = book.imageUrl;
}

Book::Book(const std::string& bookData)
{
	std::stringstream iss(bookData);
	std::string detailedData;
	std::getline(iss, detailedData, '|');
	this->bookId = detailedData;
	std::getline(iss, detailedData, '|');
	this->originalTitle = detailedData;
	std::getline(iss, detailedData, '|');
	this->author = detailedData;
	std::getline(iss, detailedData, '|');
	this->isbn = detailedData;
	std::getline(iss, detailedData, '|');
	this->imageUrl = detailedData;
}

const Book& Book::operator=(const Book& book)
{
	if (this == &book) return *this;
	this->bookId = book.bookId;
	this->originalTitle = book.originalTitle;
	this->author = book.author;
	this->isbn = book.isbn;
	this->imageUrl = book.imageUrl;
	return *this;
}

std::string Book::getBookId() const
{
	return bookId;
}

std::string Book::getIsbn() const
{
	return isbn;
}

std::string Book::getTitle() const
{
	return originalTitle;
}

std::string Book::getAuthor() const
{
	return author;
}

std::string Book::getImgUrl() const
{
	return imageUrl;
}

std::ostream& operator<<(std::ostream& fo, const Book& book)
{
	fo << book.getBookId() << ". " << book.getTitle() << ", " << book.getAuthor() << " | " << book.getIsbn();
	return fo;
}
