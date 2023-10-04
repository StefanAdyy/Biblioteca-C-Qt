#include "TCPSocket.h"

const SOCKET TCPSocket::badSocket = INVALID_SOCKET;
SOCKET TCPSocket::listenSocket = INVALID_SOCKET;
bool TCPSocket::listenSocketGenerated = false;

struct WinsockInitializer
{
	WinsockInitializer()
	{
		WSADATA wsaData;
		int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (iResult != NO_ERROR) {
			throw std::string("WSAStartup Failed with error: ") + std::to_string(iResult);
		}
	}

	~WinsockInitializer()
	{
		WSACleanup();
	}
};

WinsockInitializer globalInitializer;

TCPSocket::TCPSocket(bool isClient)
{
	if (!isClient)
	{
		ZeroMemory(&hints, sizeof(hints));
		hints.ai_family = AF_INET;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;
		hints.ai_flags = AI_PASSIVE;

		int iResult = getaddrinfo(NULL, "27015", &hints, &result);
		if (iResult != 0)
		{
			throw std::string("getaddrinfo failed with error: " + std::to_string(iResult));
		}

		listenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
		if (listenSocket == INVALID_SOCKET)
		{
			freeaddrinfo(result);
			throw std::string("Error at socket(): ") + std::to_string(WSAGetLastError());
		}
	}
	else
	{
		ZeroMemory(&hints, sizeof(hints));
		hints.ai_family = AF_UNSPEC;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;

		int iResult = getaddrinfo("localhost", "27015", &hints, &result);
		if (iResult != 0)
		{
			throw std::string("getaddrinfo failed with error: " + std::to_string(iResult));
		}

	}
}

TCPSocket::~TCPSocket()
{
	if (listenSocket != badSocket)
	{
		closesocket(listenSocket);
	}
	if (serverConnection != badSocket)
	{
		closesocket(serverConnection);
	}
}

SOCKET TCPSocket::GetListenSocket() const
{
	return listenSocket;
}

void TCPSocket::SetSocket(const SOCKET& socket)
{
	serverConnection = socket;
}

bool TCPSocket::Connect()
{
	bool connected = false;
	for (ptr = result; ptr != NULL; ptr = ptr->ai_next)
	{
		serverConnection = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
		if (serverConnection == INVALID_SOCKET)
		{
			std::cerr << "Socket failed with error: " << WSAGetLastError() << std::endl;
			return false;
		}

		int iResult = connect(serverConnection, ptr->ai_addr, (int)ptr->ai_addrlen);
		if (iResult == SOCKET_ERROR)
		{
			std::cerr << "Could not connect to server, error: " << WSAGetLastError() << std::endl;
			closesocket(serverConnection);
			serverConnection = INVALID_SOCKET;
			continue;
		}
		else
		{
			connected = true;
			break;
		}
	}
	return connected;
}

bool TCPSocket::ReceiveBool(bool& value)
{
	int iResult = recv(serverConnection, (char*)&value, sizeof(bool), NULL);
	if (iResult == SOCKET_ERROR)
		return false;

	return true;
}

bool TCPSocket::ReceiveInt(int& value)
{
	int iResult = recv(serverConnection, (char*)&value, sizeof(int), NULL);
	if (iResult == SOCKET_ERROR)
		return false;

	return true;
}

bool TCPSocket::ReceiveString(std::string& value)
{
	int bufferLength = 0;
	if (!ReceiveInt(bufferLength))
		return false;

	char* buffer = new char[bufferLength];

	int iResult = recv(serverConnection, buffer, bufferLength, NULL);
	value = std::string();
	std::copy(buffer, buffer + bufferLength, std::back_inserter(value));
	delete[]buffer;

	if (iResult == SOCKET_ERROR)
		return false;

	return true;
}

bool TCPSocket::SendBool(const bool& value)
{
	int iResult = send(serverConnection, (char*)&value, sizeof(bool), NULL);
	if (iResult == SOCKET_ERROR)
		return false;

	return true;
}

bool TCPSocket::SendInt(const int& value)
{
	int iResult = send(serverConnection, (char*)&value, sizeof(int), NULL);
	if (iResult == SOCKET_ERROR)
		return false;

	return true;
}

bool TCPSocket::SendString(const std::string& value)
{
	int bufferLength = value.size();
	if (!SendInt(bufferLength))
		return false;

	int iResult = send(serverConnection, value.c_str(), bufferLength, NULL);
	if (iResult == SOCKET_ERROR)
		return false;

	return true;
}

bool TCPSocket::Listen()
{
	if (!TCPSocket::listenSocketGenerated)
		//Bind socket
	{
		if (bind(listenSocket, result->ai_addr, (int)result->ai_addrlen) == SOCKET_ERROR) {
			std::cerr << "Bind failed with error: " << WSAGetLastError() << std::endl;
			freeaddrinfo(result);
			return false;
		}
		freeaddrinfo(result);
		//Listen for incomin connection requests on the created socket
		if (listen(listenSocket, SOMAXCONN) == SOCKET_ERROR) {
			std::cerr << "Listen failed with error: " << WSAGetLastError() << std::endl;
			return false;
		}
		TCPSocket::listenSocketGenerated = true;
	}
	return true;
}

bool TCPSocket::CloseConnection()
{
	if (closesocket(serverConnection == SOCKET_ERROR))
	{
		if (WSAGetLastError() == WSAENOTSOCK)
			return true;
		std::cerr << "Failed to close socket Error: " << WSAGetLastError() << std::endl;
		return false;
	}
	return true;
}
