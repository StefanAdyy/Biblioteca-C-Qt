#include "BorrowedBooks.h"

BorrowedBooks::BorrowedBooks(const std::string& queryResult)
{
	std::string word;
	std::stringstream result;
	result << queryResult;

	std::getline(result, word, '|');
	this->userId = std::stoi(word);

	std::getline(result, word, '|');
	this->bookId = std::stoi(word);

	std::getline(result, word, '|');
	this->borrowDate = word;

	std::getline(result, word, '|');
	this->returnDate =word;
}

BorrowedBooks::BorrowedBooks(const unsigned int& userId, const unsigned int& bookId, const std::string& returnDate, const std::string& borrowDate)
	:userId(userId), bookId(bookId) , returnDate(returnDate), borrowDate(borrowDate) {}

BorrowedBooks::BorrowedBooks(const BorrowedBooks& borrowedBook)
{
	this->userId = borrowedBook.userId;
	this->bookId = borrowedBook.bookId;
	this->borrowDate = borrowedBook.borrowDate;
	this->returnDate = borrowedBook.returnDate;
}

BorrowedBooks& BorrowedBooks::operator=(const BorrowedBooks& borrowedBook)
{
	if (this == &borrowedBook) return *this;
	this->userId = borrowedBook.userId;
	this->bookId = borrowedBook.bookId;
	this->borrowDate = borrowedBook.borrowDate;
	this->returnDate = borrowedBook.returnDate;
	return *this;
}



unsigned int BorrowedBooks::GetUserId() const
{
	return userId;
}

unsigned int BorrowedBooks::GetBookId() const
{
	return bookId;
}

std::string BorrowedBooks::GetReturnDate() const
{
	return this->returnDate;
}

std::string BorrowedBooks::GetBorrowDate() const
{
	return this->borrowDate;
}
