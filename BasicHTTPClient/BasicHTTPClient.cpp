#include "stdafx.h"
#include "BasicHTTP.h"
#include <chrono>
#include <thread>
#include "BasicHTTPClient.h"
#include "StopWatch.h"

int main()
{

	//BasicHTTP::Request("GET", "soundly.me", 80, "/", NULL, response);


	try
	{
		BasicHTTP* client = new BasicHTTP();

		while (true)
		{
            StopWatch sp; 
            sp.Start();
			string response = client->Get("localhost", 8080, "/temperature/", "userdata");
            sp.Stop();
            sp.LogElapsedVerb("GET:");
            Print(response);

            sp.Start();
			response = client->Post("localhost", 8080, "/temperature/30", "userdata");
            sp.Stop();
            sp.LogElapsedVerb("POST:");
            Print(response);
		}

	}
	catch (const std::exception& ex)
	{
		cout << &ex << endl;

	}

	//std::this_thread::sleep_for(std::chrono::milliseconds(1000));


	return 0;
	/*
	Doing a POST, note the "percent" encoding for 'opt_urlencode':

	HTTPReq("POST", "soundly.me", 80, "/not-a-real-resource",
	"userdata=%7B%22key%22%3A%5B%22value0%22%5D%7D", response);

	*/
}

void Print(std::string &response)
{
	cout << "=============================== response:"
		<< endl
		<< response
		<< endl
		<< "=============================== "
		<< endl;
}
