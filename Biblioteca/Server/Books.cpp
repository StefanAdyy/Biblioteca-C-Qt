#include "Books.h"

Books::Books(const unsigned int& id, const unsigned int& bookId, const unsigned int& bestBookId, const unsigned int& workId, const unsigned int& booksCount, const std::string& isbn, const std::string& isbn13, const std::string& authors,
	const std::string& originalPublicationYear, const std::string& originalTitle, const std::string& title, const std::string& languageCode, const double& averageRating,
	const unsigned int& ratingsCount, const unsigned int& workRatingsCount, const unsigned int& workTextReviewsCount, const unsigned int& ratings1, const unsigned int& ratings2, const unsigned int& ratings3, const unsigned int& ratings4,
	const unsigned int& ratings5, const std::string& imageUrl, const std::string& smallImageUrl) :
	id(id),
	bookId(bookId),
	bestBookId(bestBookId),
	workId(workId),
	booksCount(booksCount),
	isbn(isbn),
	isbn13(isbn13),
	authors(authors),
	originalPublicationYear(originalPublicationYear),
	originalTitle(originalTitle),
	title(title),
	languageCode(languageCode),
	averageRating(averageRating),
	ratingsCount(ratingsCount),
	workRatingsCount(workRatingsCount),
	workTextReviewsCount(workTextReviewsCount),
	ratings1(ratings1),
	ratings2(ratings2),
	ratings3(ratings3),
	ratings4(ratings4),
	ratings5(ratings5),
	imageUrl(imageUrl),
	smallImageUrl(smallImageUrl) {}

Books::Books(const std::string& queryResult)
{
	std::string word;
	std::stringstream result;
	result << queryResult;

	std::getline(result, word, '|');
	this->id = std::stoi(word);

	std::getline(result, word, '|');
	this->bookId = std::stoi(word);

	std::getline(result, word, '|');
	this->bestBookId = std::stoi(word);

	std::getline(result, word, '|');
	this->workId = std::stoi(word);

	std::getline(result, word, '|');
	this->booksCount = std::stoi(word);

	std::getline(result, word, '|');
	this->isbn = word;

	std::getline(result, word, '|');
	this->isbn13 = word;

	std::getline(result, word, '|');
	this->authors = word;

	std::getline(result, word, '|');
	this->originalPublicationYear = word;

	std::getline(result, word, '|');
	this->originalTitle = word;

	std::getline(result, word, '|');
	this->title = word;

	std::getline(result, word, '|');
	this->languageCode = word;

	std::getline(result, word, '|');
	this->averageRating = std::stod(word);

	std::getline(result, word, '|');
	this->ratingsCount = std::stoi(word);

	std::getline(result, word, '|');
	this->workRatingsCount = std::stoi(word);

	std::getline(result, word, '|');
	this->workTextReviewsCount = std::stoi(word);

	std::getline(result, word, '|');
	this->ratings1 = std::stoi(word);

	std::getline(result, word, '|');
	this->ratings2 = std::stoi(word);

	std::getline(result, word, '|');
	this->ratings3 = std::stoi(word);

	std::getline(result, word, '|');
	this->ratings4 = std::stoi(word);

	std::getline(result, word, '|');
	this->ratings5 = std::stoi(word);

	std::getline(result, word, '|');
	this->imageUrl = word;

	std::getline(result, word, '|');
	this->smallImageUrl = word;
}

Books::Books(const Books& book)
{
	this->id = book.id;
	this->bookId = book.bookId;
	this->bestBookId = book.bestBookId;
	this->workId = book.workId;
	this->booksCount = book.booksCount;
	this->isbn = book.isbn;
	this->isbn13 = book.isbn13;
	this->authors = book.authors;
	this->originalPublicationYear = book.originalPublicationYear;
	this->originalTitle = book.originalTitle;
	this->title = book.title;
	this->languageCode = book.languageCode;
	this->averageRating = book.averageRating;
	this->ratingsCount = book.ratingsCount;
	this->workRatingsCount = book.workRatingsCount;
	this->workTextReviewsCount = book.workTextReviewsCount;
	this->ratings1 = book.ratings1;
	this->ratings2 = book.ratings2;
	this->ratings3 = book.ratings3;
	this->ratings4 = book.ratings4;
	this->ratings5 = book.ratings5;
	this->imageUrl = book.imageUrl;
	this->smallImageUrl = book.smallImageUrl;
}

Books& Books::operator=(const Books& book)
{
	if (this == &book) return *this;
	this->id = book.id;
	this->bookId = book.bookId;
	this->bestBookId = book.bestBookId;
	this->workId = book.workId;
	this->booksCount = book.booksCount;
	this->isbn = book.isbn;
	this->isbn13 = book.isbn13;
	this->authors = book.authors;
	this->originalPublicationYear = book.originalPublicationYear;
	this->originalTitle = book.originalTitle;
	this->title = book.title;
	this->languageCode = book.languageCode;
	this->averageRating = book.averageRating;
	this->ratingsCount = book.ratingsCount;
	this->workRatingsCount = book.workRatingsCount;
	this->workTextReviewsCount = book.workTextReviewsCount;
	this->ratings1 = book.ratings1;
	this->ratings2 = book.ratings2;
	this->ratings3 = book.ratings3;
	this->ratings4 = book.ratings4;
	this->ratings5 = book.ratings5;
	this->imageUrl = book.imageUrl;
	this->smallImageUrl = book.smallImageUrl;
	return *this;
}

unsigned int Books::GetId() const
{
	return id;
}

unsigned int Books::GetBookId() const
{
	return bookId;
}

unsigned int Books::GetWorkId() const
{
	return workId;
}

unsigned int Books::GetBestBookId() const
{
	return bestBookId;
}

unsigned int Books::GetBookCount() const
{
	return booksCount;
}

unsigned int Books::GetRatingsCount() const
{
	return ratingsCount;
}

unsigned int Books::GetWorkRatingsCount() const
{
	return workRatingsCount;
}

unsigned int Books::GetWorkTextReviewsCount() const
{
	return workTextReviewsCount;
}

unsigned int Books::GetRatings1() const
{
	return ratings1;
}

unsigned int Books::GetRatings2() const
{
	return ratings2;
}

unsigned int Books::GetRatings3() const
{
	return ratings3;
}

unsigned int Books::GetRatings4() const
{
	return ratings4;
}

unsigned int Books::GetRatings5() const
{
	return ratings5;
}

double Books::GetAverageRating() const
{
	return averageRating;
}

std::string Books::GetISBN() const
{
	return isbn;
}

std::string Books::GetISBN13() const
{
	return isbn13;
}

std::string Books::GetLanguageCode() const
{
	return languageCode;
}

std::string Books::GetAuthors() const
{
	return authors;
}

std::string Books::GetImageURL() const
{
	return imageUrl;
}

std::string Books::GetSmallImageURL() const
{
	return smallImageUrl;
}

std::string Books::GetTitle() const
{
	return title;
}

std::string Books::GetOriginalTitle() const
{
	return originalTitle;
}

std::string Books::GetOriginalPublicationYear() const
{
	return originalPublicationYear;
}
