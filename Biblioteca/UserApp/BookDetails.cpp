#include "BookDetails.h"
#include <algorithm>

BookDetails::BookDetails(const std::string& tags, const float& averageRating, const unsigned int& ratings1, const unsigned int& ratings2, const  unsigned int& ratings3, const  unsigned int& ratings4, const  unsigned int& ratings5, const std::string& languageCode, const std::string& imageUrl) :

	tags(tags),
	averageRating(averageRating),
	ratings1(ratings1),
	ratings2(ratings2),
	ratings3(ratings3),
	ratings4(ratings4),
	ratings5(ratings5),
	languageCode(languageCode),
	imageUrl(imageUrl)
{
}

BookDetails::BookDetails(const std::string& data)
{
	std::stringstream getData(data);
	std::string word;

	std::getline(getData, word, '|');
	tags = word;

	std::getline(getData, word, '|');
	averageRating = std::stof(word);

	std::getline(getData, word, '|');
	ratings1 = std::stoi(word);

	std::getline(getData, word, '|');
	ratings2 = std::stoi(word);

	std::getline(getData, word, '|');
	ratings3 = std::stoi(word);

	std::getline(getData, word, '|');
	ratings4 = std::stoi(word);

	std::getline(getData, word, '|');
	ratings5 = std::stoi(word);

	std::getline(getData, word, '|');
	languageCode = word;

	std::getline(getData, word, '|');
	imageUrl = word;
}

const BookDetails& BookDetails::operator=(const BookDetails& bookDetails)
{
	if (this == &bookDetails) return *this;
	this->tags = bookDetails.tags;
	this->averageRating = bookDetails.averageRating;
	this->ratings1 = bookDetails.ratings1;
	this->ratings2 = bookDetails.ratings2;
	this->ratings3 = bookDetails.ratings3;
	this->ratings4 = bookDetails.ratings4;
	this->ratings5 = bookDetails.ratings5;
	this->languageCode = bookDetails.languageCode;
	this->imageUrl = bookDetails.imageUrl;
	return *this;
}

std::string BookDetails::GetTags() const
{
	return tags;
}

float BookDetails::GetAverageRating() const
{
	return averageRating;
}

unsigned int BookDetails::GetRatings1() const
{
	return ratings1;
}

unsigned int BookDetails::GetRatings2() const
{
	return ratings2;
}

unsigned int BookDetails::GetRatings3() const
{
	return ratings3;
}

unsigned int BookDetails::GetRatings4() const
{
	return ratings4;
}

unsigned int BookDetails::GetRatings5() const
{
	return ratings5;
}

std::string BookDetails::GetLanguageCode() const
{
	return languageCode;
}

std::string BookDetails::GetImageUrl() const
{
	return imageUrl;
}
