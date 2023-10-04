#pragma once
#include <iostream>
#include <string>
#include <sstream>
class BorrowedBooks
{
public:
	BorrowedBooks() = default;
	BorrowedBooks(const std::string& queryResult);
	BorrowedBooks(const unsigned int& userId, const unsigned int& bookId, const std::string& returnDate, const std::string& borrowDate);
	BorrowedBooks(const BorrowedBooks& borrowedBook);
	~BorrowedBooks() = default;

	BorrowedBooks& operator=(const BorrowedBooks& borrowedBook);

	unsigned int GetUserId()const;
	unsigned int GetBookId()const;
	std::string GetReturnDate()const;
	std::string GetBorrowDate()const;
private:
	std::string returnDate, borrowDate;
	unsigned int userId, bookId;
};

