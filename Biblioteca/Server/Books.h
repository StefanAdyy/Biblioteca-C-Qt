#pragma once
#include <iostream>
#include <sstream>

class Books
{
public:
	Books() = default;
	Books(const unsigned int& id, const unsigned int& bookId, const unsigned int& bestBookId, const unsigned int& workId, const unsigned int& booksCount, const std::string& isbn, const std::string& isbn13, const std::string& authors,
		const std::string& originalPublicationYear, const std::string& originalTitle, const std::string& title, const std::string& languageCode, const double& averageRating,
		const unsigned int& ratingsCount, const unsigned int& workRatingsCount, const unsigned int& workTextReviewsCount, const unsigned int& ratings1, const unsigned int& ratings2, const unsigned int& ratings3, const unsigned int& ratings4,
		const unsigned int& ratings5, const std::string& imageUrl, const std::string& smallImageUrl);
	Books(const std::string& queryResult);
	Books(const Books& book);
	~Books() = default;

	Books& operator=(const Books& book);

	unsigned int GetId() const;
	unsigned int GetBookId() const;
	unsigned int GetWorkId() const;
	unsigned int GetBestBookId() const;
	unsigned int GetBookCount() const;
	unsigned int GetRatingsCount() const;
	unsigned int GetWorkRatingsCount() const;
	unsigned int GetWorkTextReviewsCount() const;
	unsigned int GetRatings1() const;
	unsigned int GetRatings2() const;
	unsigned int GetRatings3() const;
	unsigned int GetRatings4() const;
	unsigned int GetRatings5() const;
	double GetAverageRating() const;
	std::string GetISBN() const;
	std::string GetISBN13() const;
	std::string GetLanguageCode() const;
	std::string GetAuthors() const;
	std::string GetImageURL() const;
	std::string GetSmallImageURL() const;
	std::string GetTitle() const;
	std::string GetOriginalTitle() const;
	std::string GetOriginalPublicationYear() const;
private:
	unsigned int id, bookId, bestBookId, workId, booksCount, ratingsCount, workRatingsCount, workTextReviewsCount, ratings1, ratings2, ratings3, ratings4, ratings5;
	std::string isbn, isbn13, authors, originalPublicationYear, originalTitle, title, languageCode, imageUrl, smallImageUrl;
	double averageRating;

};
