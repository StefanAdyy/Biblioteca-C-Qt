#pragma once
#include <iostream>
#include <string>
#include <sstream>

class UserServer
{
public:
	UserServer() = default;
	UserServer(const UserServer& userserver);
	UserServer(const std::string queryResult);
	UserServer(const int& userId, const std::string& username, const std::string& password);

	void SetUserId(const int& userId);
	void SetUsername(const std::string& username);
	void SetPassword(const std::string& password);

	int GetUserId() const;
	std::string GetUsername() const;
	std::string GetPassword() const;
	UserServer& operator=(const UserServer& userserver);

	~UserServer() = default;
private:
	int userId;
	std::string username, password;
};

