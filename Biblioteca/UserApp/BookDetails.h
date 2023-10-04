#pragma once
#include <vector>
#include <iostream>
#include <sstream>
class BookDetails
{
public:
	BookDetails() = default;
	BookDetails(const std::string& tags,const float& averageRating,const unsigned int& ratings1, const unsigned int& ratings2,const  unsigned int& ratings3, const  unsigned int& ratings4, const  unsigned int& ratings5,const std::string& languageCode,const std::string& imageUrl);
	BookDetails(const std::string& data);
	~BookDetails() = default;

	const BookDetails& operator=(const BookDetails& bookDetails);

	std::string GetTags() const;
	float GetAverageRating() const;
	unsigned int GetRatings1() const;
	unsigned int GetRatings2() const;
	unsigned int GetRatings3() const;
	unsigned int GetRatings4() const;
	unsigned int GetRatings5() const;
	std::string GetLanguageCode() const;
	std::string GetImageUrl() const;
private:
	float averageRating;
	unsigned int ratings1, ratings2, ratings3, ratings4, ratings5;
	std::string languageCode,imageUrl,tags;
};

