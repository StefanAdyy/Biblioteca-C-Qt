#pragma once
#include "Books.h"
#include "Database.h"
#include "BorrowedBooks.h"
#include "UserServer.h"
#include "Query.h"
#include <sstream>
#include <string>
#include <vector>
#include "..\TCPSocket\TCPSocket.h"

class Server
{
public:
	Server();
	void RunServer();
	~Server()=default;
private:
	Query queryList;
	Books book;
	Database database;
	UserServer user;
	std::vector<BorrowedBooks> borrowedBooks;
	TCPSocket clientConnections[100];
	std::thread connectionThreads[100];
	unsigned int connectionCounter = 0;

	void PrepareVirtualTable();
	void DropVirtualTable();
	bool ListenForNewConnection();

	bool ProcessData(const unsigned int& index);
	void ClientHandler(const unsigned int& index);

	void Register(const unsigned int& index);
	void Login(const unsigned int& index);
	void DeleteUser(const unsigned int& index);
	void Logout(const unsigned int& index);
	void ReturnBook(const unsigned int& index);
	void BorrowBook(const unsigned int& index);
	void SearchBook(const unsigned int& index);
	void ChangePassword(const unsigned int& index);
	void PrepareBookDetails(const unsigned int& index);
	void ProlongBorrowDate(const unsigned int& index);

	void RemoveInvalidCharacters(std::string& string);
};

