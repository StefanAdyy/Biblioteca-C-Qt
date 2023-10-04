#include "..\TCPSocket\TCPSocket.cpp"
#include "User.h"

User user = User();

unsigned int User::option = 0;

User::User()
{
	client.Connect();
	this->username = "";
	this->password = "";
	this->borrowedBooks.resize(0);
	isLoggedIn = false;
}

User::User(const std::string& username, const std::string& password, const std::vector<BorrowedBooks>& borrowedBooks)
{
	client.Connect();
	this->username = username;
	this->borrowedBooks = borrowedBooks;
	this->password = password;
	isLoggedIn = true;
}

User::User(const std::string& username, const std::string& password)
{
	client.Connect();
	this->username = username;
	this->password = password;
	this->borrowedBooks.resize(0);
	isLoggedIn = true;
}

User::User(const User& user)
{
	this->username = user.username;
	this->borrowedBooks = user.borrowedBooks;
	this->password = user.password;
	this->isLoggedIn = user.isLoggedIn;
}

std::string User::GetUsername() const
{
	return username;
}

std::string User::GetPassword() const
{
	return password;
}

void User::SetUsername(const std::string& username)
{
	this->username = username;
}

void User::SetPassword(const std::string& password)
{
	this->password = password;
}

std::vector<Book> User::GetSearchedBooks() const
{
	return searchedBooks;
}

std::vector<BorrowedBooks> User::GetBorrowedBooks() const
{
	return borrowedBooks;
}

std::vector<std::string> User::GetCurrentBookTags() const
{
	return currentBookTags;
}

BookDetails User::GetBookDetails() const
{
	return selectedBook;
}

unsigned int User::GetOption() const
{
	return option;
}

void User::SetOption(const unsigned int& option)
{
	this->option = option;
}

unsigned int User::GetBookId() const
{
	return bookId;
}

void User::SetBookId(const unsigned int& bookId)
{
	this->bookId = bookId;
}

std::string User::GetKeyword() const
{
	return keyword;
}

void User::SetKeyword(const std::string& keyword)
{
	this->keyword = keyword;
}

bool User::GetServerError() const
{
	return serverError;
}

bool User::GetLoginStatus() const
{
	return isLoggedIn;
}

const bool& User::operator==(const User& s) const
{
	return (this == &s);
}

void User::RegisterMenu(std::string username, std::string password)
{
	client.SendInt(registerUser);
	client.SendString(username);
	client.SendString(password);
	client.ReceiveBool(serverError);
	if (!serverError)
	{
		user.username = username;
		user.password = password;
	}
	else
	{
		user.username = "";
		user.password = "";
	}
	user.isLoggedIn = false;
}

void User::LoginMenu(std::string username, std::string password)
{
	client.SendInt(loginUser);
	int borrowedBooksSize;
	client.SendString(username);
	client.SendString(password);
	client.ReceiveBool(serverError);
	borrowedBooks.clear();
	if (serverError)
	{
		user.username = username;
		user.password = password;
		user.isLoggedIn = true;
		client.ReceiveInt(borrowedBooksSize);
		borrowedBooks.resize(borrowedBooksSize);
		for (unsigned int i = 0; i < borrowedBooksSize; i++)
		{
			std::string bookToAdd;
			client.ReceiveString(bookToAdd);
			borrowedBooks[i] = BorrowedBooks(bookToAdd);
		}
	}
	else
	{
		user.username = "";
		user.password = "";
		user.isLoggedIn = false;
	}
}

void User::DeleteAccount()
{
	client.SendInt(deleteAccount);
	client.SendString(username);
	client.SendString(password);
	username = "";
	password = "";
	borrowedBooks.clear();
	currentBookTags.clear();
	isLoggedIn = false;
}

void User::Logout()
{
	client.SendInt(logout);
	username = "";
	password = "";
	borrowedBooks.clear();
	currentBookTags.clear();
	selectedBook = BookDetails();
	isLoggedIn = false;
}

void User::ReturnBook(unsigned int bookToReturnId)
{
	client.SendInt(returnBook);
	client.SendString(username);
	client.SendString(password);
	client.SendInt(bookToReturnId);
	unsigned int i;
	for (i = 0; i < borrowedBooks.size(); i++)
	{
		if (std::stoi(borrowedBooks[i].getBook().getBookId()) == bookToReturnId)
		{
			break;
		}
	}
	borrowedBooks.erase(borrowedBooks.begin() + i, borrowedBooks.begin() + i + 1);
}

void User::Borrowing(unsigned int bookToBorrowId)
{
	BorrowedBooks borrowedBook;
	client.SendInt(borrowBook);
	client.SendString(username);
	client.SendString(password);
	std::string date;
	time_t now = time(0);
	tm currentDate;
	localtime_s(&currentDate, &now);
	date = "";
	date += std::to_string(currentDate.tm_year + 1900) + '-' + std::to_string(currentDate.tm_mon + 1) + '-' + std::to_string(currentDate.tm_mday);

	client.SendInt(bookToBorrowId);
	client.SendString(date);
	borrowedBook.setBorrowingDate(date);

	const time_t one_day = 24 * 60 * 60;
	time_t date_seconds = mktime(&currentDate) + (14 * one_day);

	localtime_s(&currentDate, &date_seconds);

	date = "";
	date += std::to_string(currentDate.tm_year + 1900) + '-' + std::to_string(currentDate.tm_mon + 1) + '-' + std::to_string(currentDate.tm_mday);
	client.SendString(date);
	borrowedBook.setReturningDate(date);
	client.ReceiveBool(serverError);

	if (!serverError)
	{
		for (auto& i : searchedBooks)
		{
			if (std::stoi(i.getBookId()) == bookId)
			{
				borrowedBook.setBook(i);
				borrowedBooks.push_back(borrowedBook);
				break;
			}
		}
	}
}

void User::SearchBooks(const std::string& keyword)
{
	client.SendInt(searchBook);
	int size;
	std::string book;
	client.SendString(keyword);
	client.ReceiveInt(size);
	searchedBooks.resize(size);
	for (unsigned int i = 0; i < searchedBooks.size(); i++)
	{
		client.ReceiveString(book);
		searchedBooks[i] = Book(book);
	}
}

void User::ChangePassword(std::string newPassword)
{
	if (PasswordRequirements(newPassword))
	{
		client.SendInt(changePassword);
		client.SendString(username);
		client.SendString(password);
		client.SendString(newPassword);
		this->password = newPassword;
	}
}

void User::CreateBookDetails(const unsigned int& bookId)
{
	client.SendInt(bookDetails);
	client.SendInt(bookId);
	std::string bookDetailsData;
	client.ReceiveString(bookDetailsData);
	selectedBook = BookDetails(bookDetailsData);
}

void User::ProlongBorrowDate(const unsigned int& bookId, const std::string& returnDate)
{
	client.SendInt(prolongBorrowDate);
	client.SendString(username);
	client.SendString(password);
	std::stringstream iss(returnDate);
	std::string date;
	time_t now = time(0);
	tm retDate;
	localtime_s(&retDate, &now);

	std::getline(iss, date, '-');
	retDate.tm_year = stoi(date) - 1900;
	std::getline(iss, date, '-');
	retDate.tm_mon = stoi(date) - 1;
	std::getline(iss, date, '-');
	retDate.tm_mday = stoi(date);

	const time_t one_day = 24 * 60 * 60;
	time_t date_seconds = mktime(&retDate) + (14 * one_day);

	localtime_s(&retDate, &date_seconds);
	date = "";
	date += std::to_string(retDate.tm_year + 1900) + '-' + std::to_string(retDate.tm_mon + 1) + '-' + std::to_string(retDate.tm_mday);

	for (auto& i : borrowedBooks)
	{
		if (std::stoi(i.getBook().getBookId()) == bookId)
			i.setReturningDate(date);
	}

	client.SendInt(bookId);
	client.SendString(date);
}

bool User::PasswordRequirements(std::string pw)
{
	bool UpperLetter = false;
	bool LowerLetter = false;
	bool isDigit = false;
	bool specialChar = false;
	for (unsigned int i = 0; i < pw.length(); i++)
	{
		if (isupper(pw[i]))
		{
			UpperLetter = true;
		}
		if (islower(pw[i]))
		{
			LowerLetter = true;
		}
		if (isdigit(pw[i]))
		{
			isDigit = true;
		}
		if ((pw[i] > 32 && pw[i] < 48) || (pw[i] > 57 && pw[i] < 65) || (pw[i] > 90 && pw[i] < 97) || (pw[i] > 122 && pw[i] < 127))
		{
			specialChar = true;
		}
	}
	if (pw.find('\'') != std::string::npos)
		return false;
	if (UpperLetter == false || LowerLetter == false)
		return false;

	if (isDigit == false)
		return false;

	if (specialChar == false)
		return false;
	return true;
}

bool User::CheckMaxProlongedDate(const BorrowedBooks& borrowedBooks)
{
	std::stringstream iss(borrowedBooks.getBorrowDate());
	std::string date;
	time_t now = time(0);
	tm borrowDate, retDate;
	localtime_s(&borrowDate, &now);

	std::getline(iss, date, '-');
	borrowDate.tm_year = stoi(date) - 1900;
	std::getline(iss, date, '-');
	borrowDate.tm_mon = stoi(date) - 1;
	std::getline(iss, date, '-');
	borrowDate.tm_mday = stoi(date);

	iss.str(std::string());
	iss.clear();
	iss << borrowedBooks.getReturningDate();
	date = std::string();
	localtime_s(&retDate, &now);

	std::getline(iss, date, '-');
	retDate.tm_year = stoi(date) - 1900;
	std::getline(iss, date, '-');
	retDate.tm_mon = stoi(date) - 1;
	std::getline(iss, date, '-');
	retDate.tm_mday = stoi(date);

	std::time_t borrowSeconds = std::mktime(&borrowDate);
	std::time_t returnSeconds = std::mktime(&retDate);
	double daysBorrowed = std::difftime(returnSeconds, borrowSeconds) / (60 * 60 * 24);
	if (daysBorrowed >= 42.)
		return false;
	return true;
}

bool User::CheckOverdueBooks()
{
	std::stringstream iss;
	std::string date;
	time_t now = time(0);
	tm retDate;
	double dateDifference;
	for (auto& i : borrowedBooks)
	{
		iss.str(std::string());
		iss.clear();
		iss << i.getReturningDate();
		date = std::string();
		localtime_s(&retDate, &now);

		std::getline(iss, date, '-');
		retDate.tm_year = stoi(date) - 1900;
		std::getline(iss, date, '-');
		retDate.tm_mon = stoi(date) - 1;
		std::getline(iss, date, '-');
		retDate.tm_mday = stoi(date);
		dateDifference = std::difftime(std::mktime(&retDate), now);
		if (dateDifference < 0)
			return false;
	}
	return true;
}

void User::ClientHandler()
{
	while (true)
	{
		if (option != 0)
		{
			if (!user.ProcessData())
			{
				break;
			}
		}
	}
	std::cout << "Lost connection to the server" << std::endl;
	if (user.client.CloseConnection())
	{
		std::cout << "Socket to server was closed successfully" << std::endl;
	}
}

bool User::ProcessData()
{
	switch (option)
	{
	case 1:
	{
		RegisterMenu(user.username, user.password);
		break;
	}
	case 2:
	{
		LoginMenu(user.username, user.password);
		break;
	}
	case 3:
	{
		DeleteAccount();
		break;
	}
	case 4:
	{
		Logout();
		break;
	}
	case 5:
	{
		ReturnBook(bookId);
		break;
	}
	case 6:
	{
		Borrowing(bookId);
		break;
	}
	case 7:
	{
		SearchBooks(keyword);
		break;
	}
	case 8:
	{
		ChangePassword(keyword);
		break;
	}
	case 9:
	{
		CreateBookDetails(bookId);
		break;
	}

	case 10:
	{
		std::string returnDate;
		for (auto& i : user.borrowedBooks)
		{
			if (std::stoi(i.getBook().getBookId()) == bookId)
			{
				returnDate = i.getReturningDate();
				break;
			}
		}
		ProlongBorrowDate(bookId, returnDate);
		break;
	}
	default:
		break;
	}
	option = 0;
	return true;
}
