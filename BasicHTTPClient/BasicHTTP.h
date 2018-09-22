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

	void Connect(const char * hostname, int port);

	void static Request(
		const char* verb,
		const char* hostname,
		int port,
		const char* resource,
		const char* opt_urlencoded,
		string& response);
};

