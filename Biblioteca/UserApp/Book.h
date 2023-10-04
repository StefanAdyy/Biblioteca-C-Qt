#pragma once
#include <string>
#include <sstream>

class Book {

private:
	std::string bookId;
	std::string originalTitle;
	std::string author;
	std::string isbn;
	std::string imageUrl;

public:
	Book() = default;
	Book(const std::string& id, const std::string& title, const std::string& auth, const std::string& ISBNcode, const std::string& imgURL);
	Book(const Book& book);
	Book(const std::string& serverReceived);

	const Book& operator=(const Book& book);

	std::string getBookId() const;
	std::string getIsbn() const;
	std::string getTitle() const;
	std::string getAuthor() const;
	std::string getImgUrl() const;

	friend std::ostream& operator<<(std::ostream& fo, const Book& book);

};