#include "stdafx.h"
#include "BasicHTTP.h"
#define DEFAULT_BUFLEN 512

BasicHTTP::BasicHTTP()
{
}

BasicHTTP::~BasicHTTP()
{
	Disconnect();
}

void BasicHTTP::Connect(const char * hostname, int port)
{
	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != NO_ERROR)
	{
		cout << "WSAStartup failed. The failure code is:" << iResult << "\n";
		exit(1);
	}

	win_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (win_socket == INVALID_SOCKET)
	{
		cout << "Could not connect. The error code is:" << WSAGetLastError() << "\n";
		WSACleanup();
		exit(1);
	}

	struct hostent *host;
	host = gethostbyname(hostname);

	//https://docs.microsoft.com/en-us/windows/desktop/winsock/sockaddr-2
	char* localIP = inet_ntoa(*(struct in_addr *)*host->h_addr_list);

	SOCKADDR_IN SockAddr;
	SockAddr.sin_port = htons(port);
	SockAddr.sin_family = AF_INET;
	SockAddr.sin_addr.s_addr = inet_addr(localIP);


	cout << "Connecting...\n";

	iResult = connect(win_socket, (SOCKADDR*)(&SockAddr), sizeof(SockAddr));
	if (iResult == SOCKET_ERROR)
	{
		cout << "Could not connect. The error code is:" << iResult;
		Disconnect();
		exit(1);
	}
	cout << "Connected.\n";
}

void BasicHTTP::Disconnect()
{
	closesocket(win_socket);
	WSACleanup();
}

void BasicHTTP::Get(const char * hostname, int port, const char * resource, const char * opt_urlencoded, string & response)
{
	Connect(hostname, port);

	// Build request
	string req = "GET";
	req.append(" ");
	req.append(resource);
	req.append(" HTTP/1.1\r\n");

	req.append("Host: ");
	req.append(hostname);
	req.append(":");
	req.append(to_string(port));
	req.append("\r\n");
	req.append("Cache-Control: no-cache\r\n");
	req.append("Connection: close\r\n\r\n");

	cout << "=============================== GET"
		<< endl
		<< req
		<< endl
		<< "=============================== "
		<< endl;

	Send(req);

	Receive(response);

	Disconnect();
}

void BasicHTTP::Post(const char * hostname, int port, const char * resource, const char * opt_urlencoded, string & response)
{
	Connect(hostname, port);

	// Build request
	string req = "POST";
	req.append(" ");
	req.append(resource);
	req.append(" HTTP/1.1\r\n");

	req.append("Host: ");
	req.append(hostname);
	req.append(":");
	req.append(to_string(port));
	req.append("\r\n");


	req.append("Cache-Control: no-cache\r\n");
	req.append("Content-length: ");
	req.append(to_string(strlen(opt_urlencoded)));
	req.append("\r\n");
	req.append("Content-Type: application/x-www-form-urlencoded\r\n\r\n");

	// User is required to handle URI encoding for this value
	req.append(opt_urlencoded);

	cout << "=============================== POST"
		<< endl
		<< req
		<< endl
		<< "=============================== "
		<< endl;

	Send(req);

	Receive(response);

	Disconnect();
}

void BasicHTTP::Send(std::string &req)
{
	int iResult = send(win_socket, req.c_str(), req.size(), 0);
	if (iResult == SOCKET_ERROR)
		cout << "send failed: %d\n" << WSAGetLastError();
	else
		cout << "Bytes Sent: %ld\n" << iResult;
}


void BasicHTTP::Receive(std::string & response)
{
	char buffer[DEFAULT_BUFLEN];
	int iResult;
	do
	{
		iResult = recv(win_socket, buffer, 200, 0);

		if (iResult > 0)
			response.append(buffer, 0, iResult);
		else if (iResult == 0)
			cout << "Connection closed.\n";
		else
			cout << "Receive failed: %d\n" << WSAGetLastError();


	} while (iResult > 0);
}
