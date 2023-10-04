#pragma once
#include <string>
class Query
{
public:
	std::string BooksBookSearch(const std::string& searchInput)const;
	std::string BooksNumOfBookSearch(const std::string& searchInput)const;
	std::string BorrowedBooksSearch(const unsigned int& userIdSearch)const;
	std::string BorrowedBooksBookAlreadyBorrowed(const unsigned int& userId, const unsigned int& bookId)const;
	std::string BorrowedBooksInsert(const unsigned int& userId, const unsigned int& bookId,const std::string& borrowedDate,const std::string& returningDate)const;
	std::string BorrowedBooksDelete(const unsigned int& userId, const unsigned int& bookId)const;
	std::string BorrowedBooksUpdateReturnDate(const unsigned int& userId, const unsigned int& bookId,const std::string &date)const;
	std::string BookGetBookByID(const  unsigned int& bookId) const;
	std::string TagsGetAllTags(const unsigned int& goodReadsBookId);
	std::string UserServerUserSearch(const std::string& usernameSearch, const std::string& passwordSearch)const;
	std::string UserServerUserInsert(const std::string& username, const std::string& password)const;
	std::string UserServerUserDelete(const std::string& username, const std::string& password)const;
	std::string UserServerCheckExistingUsers(const std::string& username)const;
	std::string UserServerUsersLogin(const std::string& username, const std::string& password)const;
	std::string UserServerUsersLoginID(const std::string& username, const std::string& password)const;
	std::string UserChangePassword(const unsigned int& userId, const std::string& newPassword)const;
};

