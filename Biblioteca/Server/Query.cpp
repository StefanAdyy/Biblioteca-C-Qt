#include "Query.h"

std::string Query::BooksBookSearch(const std::string& searchInput) const
{
	std::string query = "Select * from Books where id in (SELECT rank from demo where editdist3(word,'";
	query += searchInput;
	query += "')/100 < 10);";
	return query;
}
std::string Query::BooksNumOfBookSearch(const std::string& searchInput) const
{
	std::string query = "Select count(*) from Books where id in (SELECT rank from demo where editdist3(word,'";
	query += searchInput;
	query += "')/100 < 5 ORDER BY editdist3(word,'" + searchInput + "')); ";
	return query;
}
std::string Query::BorrowedBooksSearch(const unsigned int& userIdSearch) const
{
	std::string query = "SELECT * FROM BorrowedBooks WHERE user_id=";
	query += std::to_string(userIdSearch);
	return query;
}
std::string Query::BorrowedBooksBookAlreadyBorrowed(const unsigned int& userId, const unsigned int& bookId) const
{
	std::string query = "SELECT COUNT(*) FROM BorrowedBooks WHERE user_id = '";
	query += std::to_string(userId) + "' AND book_id = '" + std::to_string(bookId) + "'";
	return query;
}
std::string Query::BorrowedBooksInsert(const unsigned int& userId, const unsigned int& bookId, const std::string& borrowedDate, const std::string& returningDate) const
{
	std::string query = "INSERT INTO BorrowedBooks (user_id,book_id,borrowed_date,returning_date)VALUES ('";
	query += std::to_string(userId) + "'," + "'" + std::to_string(bookId) + "'," + "'" + borrowedDate + "'," + "'" + returningDate + "')";
	return query;
}
std::string Query::BorrowedBooksDelete(const unsigned int& userId, const unsigned int& bookId) const
{
	std::string query = "DELETE FROM BorrowedBooks WHERE user_id = ";
	query += std::to_string(userId) + " AND book_id = " + std::to_string(bookId);
	return query;
}
std::string Query::BorrowedBooksUpdateReturnDate(const unsigned int& userId, const unsigned int& bookId, const std::string& date) const
{
	std::string query = "UPDATE BorrowedBooks SET returning_date = '" + date + "' WHERE user_id = " + std::to_string(userId) + " AND  book_id = " + std::to_string(bookId) + ";";
	return query;
}
std::string Query::BookGetBookByID(const unsigned int& bookId) const
{
	std::string query = "SELECT * FROM Books WHERE id = ";
	query += std::to_string(bookId);
	return query;
}
std::string Query::TagsGetAllTags(const unsigned int& goodReadsBookId)
{
	std::string query = "SELECT tag_name FROM Tags WHERE tag_id IN (SELECT tag_id FROM BookTags INNER JOIN Books o ON goodreads_book_id = o.best_book_id WHERE goodreads_book_id = ";
	query += std::to_string(goodReadsBookId) + ")";
	return query;
}
std::string Query::UserServerUserSearch(const std::string& usernameSearch, const std::string& passwordSearch) const
{
	std::string query = "SELECT * FROM User	WHERE username='";
	query += usernameSearch;
	query += "' AND password='";
	query += passwordSearch + "'";
	return query;
}
std::string Query::UserServerUserInsert(const std::string& username, const std::string& password) const
{

	std::string query = "INSERT INTO User (username,password) VALUES ('";
	query += username + "'," + "'" + password + "')";
	return query;
}
std::string Query::UserServerUserDelete(const std::string& username, const std::string& password) const
{
	std::string query = "DELETE FROM User WHERE username = '";
	query += username + "' AND password = '" + password + "'";
	return query;
}
std::string Query::UserServerCheckExistingUsers(const std::string& username) const
{
	std::string query = "SELECT COUNT(*) FROM User WHERE username='";
	query += username + "'";
	return query;
}
std::string Query::UserServerUsersLogin(const std::string& username, const std::string& password) const
{
	std::string query = "SELECT COUNT(*) FROM User WHERE username='";
	query += username + "' AND password ='" + password + "'";
	return query;
}
std::string Query::UserServerUsersLoginID(const std::string& username, const std::string& password) const
{
	std::string query = "SELECT user_id FROM User WHERE username='";
	query += username + "' AND password ='" + password + "'";
	return query;
}
std::string Query::UserChangePassword(const unsigned int& userId, const std::string& newPassword) const
{
	std::string query = "UPDATE User SET password = '";
	query += newPassword + "' WHERE user_id = " + std::to_string(userId);
	return query;
}

