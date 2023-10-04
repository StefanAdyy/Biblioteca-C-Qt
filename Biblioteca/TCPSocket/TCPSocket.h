#pragma once
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <stdio.h>

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")

class TCPSocket
{
private:

	SOCKET serverConnection;
	static SOCKET listenSocket;
	const static SOCKET badSocket;
	addrinfo* result;
	addrinfo* ptr = NULL;
	addrinfo hints;
	static bool listenSocketGenerated;
public:
	TCPSocket(bool isClient = false);
	~TCPSocket();

	SOCKET GetListenSocket() const;
	void SetSocket(const SOCKET& socket);

	bool Connect();
	bool CloseConnection();
	bool Listen();

	bool ReceiveBool(bool& value);
	bool ReceiveInt(int& value);
	bool ReceiveString(std::string& value);
	bool SendBool(const bool& value);
	bool SendInt(const int& value);
	bool SendString(const std::string& value);

};