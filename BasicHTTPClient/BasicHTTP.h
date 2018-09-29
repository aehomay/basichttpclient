#pragma once

#include <string>
#include <iostream>
#include <winsock2.h>
#include <windows.h>

using namespace std;

class BasicHTTP
{
public:
	BasicHTTP();
	~BasicHTTP();

	void Get(
		const char* hostname,
		int port,
		const char* resource,
		const char* opt_urlencoded,
		string& response);

	void Send(std::string &req);

	void Post(
		const char* hostname,
		int port,
		const char* resource,
		const char* opt_urlencoded,
		string& response);

	void Receive(std::string & response);

private:
	void  Connect(
		const char * hostname,
		int port);

	void Disconnect();

	SOCKET win_socket = INVALID_SOCKET;
};