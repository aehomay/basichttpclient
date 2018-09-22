#include "stdafx.h"
#include "BasicHTTP.h"
#include <chrono>
#include <thread>


int main()
{
	string response;
	//BasicHTTP::Request("GET", "soundly.me", 80, "/", NULL, response);

	
		try
		{
			BasicHTTP::Request("POST", "localhost", 8080, "/temperature/26.5","userdata", response);

		}
		catch (const std::exception& ex)
		{
			cout << &ex <<endl;
	
		}
				
		//std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	cout << "=============================== response:"
		<< endl
		<< response
		<< endl
		<< "=============================== "
		<< endl;
	std::getchar();

	return 0;
	/*
	Doing a POST, note the "percent" encoding for 'opt_urlencode':

	HTTPReq("POST", "soundly.me", 80, "/not-a-real-resource",
	"userdata=%7B%22key%22%3A%5B%22value0%22%5D%7D", response);

	*/
}