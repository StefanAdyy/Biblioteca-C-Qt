#include "UserServer.h"

UserServer::UserServer(const UserServer& userserver)
{
	this->userId = userserver.GetUserId();
	this->username = userserver.GetUsername();
	this->password = userserver.GetPassword();
}

UserServer::UserServer(const std::string queryResult)
{
	std::string word;
	std::stringstream result;
	result << queryResult;

	std::getline(result, word, '|');
	this->userId = std::stoi(word);

	std::getline(result, word, '|');
	this->username = word;

	std::getline(result, word, '|');
	this->password = word;
}

UserServer::UserServer(const int& userId, const std::string& username, const std::string& password) :
	userId(userId), username(username), password(password) {}


void UserServer::SetUserId(const int& userId)
{
	this->userId = userId;
}

void UserServer::SetUsername(const std::string& username)
{
	this->username = username;
}

void UserServer::SetPassword(const std::string& password)
{
	this->password = password;
}

int UserServer::GetUserId() const
{
	return userId;
}

std::string UserServer::GetUsername() const
{
	return username;
}

std::string UserServer::GetPassword() const
{
	return password;
}

UserServer& UserServer::operator=(const UserServer& userserver)
{
	if (this == &userserver) 
		return *this;
	this->userId = userserver.GetUserId();
	this->username = userserver.GetUsername();
	this->password = userserver.GetPassword();
	return *this;
}
