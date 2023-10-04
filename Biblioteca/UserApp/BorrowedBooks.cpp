#include "BorrowedBooks.h"
#include <sstream>
#include <string>
#include <iostream>
#include <vector>

BorrowedBooks::BorrowedBooks(const std::string& data)
{
	std::string word,bookData;
	std::stringstream stream(data);
	
	for (int i = 0; i < 5; i++)
	{
		std::getline(stream, word, '|');
		bookData += word+'|';
	}
	this->book=Book(bookData);
	std::getline(stream, word, '|');
	this->dateWhenBorrowed = word;
	std::getline(stream, word, '|');
	this->returningDate = word;
}

BorrowedBooks::BorrowedBooks(const Book& book, const std::string& borrowDate, const std::string& retDate)
	:book(book), dateWhenBorrowed(borrowDate), returningDate(retDate)
{
}

BorrowedBooks::BorrowedBooks(const BorrowedBooks& borrowedBook)
{
	this->book = borrowedBook.book;
	this->dateWhenBorrowed = borrowedBook.dateWhenBorrowed;
	this->returningDate = borrowedBook.returningDate;
}

BorrowedBooks BorrowedBooks::operator=(const BorrowedBooks& borrowedBook)
{
	if (this == &borrowedBook) return *this;
	this->book = borrowedBook.book;
	this->dateWhenBorrowed = borrowedBook.dateWhenBorrowed;
	this->returningDate = borrowedBook.returningDate;
	return *this;
}

Book BorrowedBooks::getBook() const
{
	return this->book;
}

std::string BorrowedBooks::getBorrowDate() const
{
	return dateWhenBorrowed;
}

std::string BorrowedBooks::getReturningDate() const
{
	return returningDate;
}

void BorrowedBooks::setBorrowingDate(const std::string& dateWhenBorrowed)
{
	this->dateWhenBorrowed = dateWhenBorrowed;
}

void BorrowedBooks::setReturningDate(const std::string& returningDate)
{
	this->returningDate = returningDate;
}

void BorrowedBooks::setBook(const Book& book)
{
	this->book = book;
}
