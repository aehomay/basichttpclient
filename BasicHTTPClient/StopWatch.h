#pragma once
#include <iostream>
#include <fstream>
#include <time.h>
#include <string>
#include <Windows.h>

class StopWatch
{
private:
    LARGE_INTEGER Frequency;
    LARGE_INTEGER StartingTime, EndingTime;

    int WriteLog(const char *msg)
    {
        int iteration = 0;

        char const *path;
        path = "C:\\performance.log";
        std::ofstream ofs((const char*)path, std::ios_base::app);
        if (ofs.is_open())
        {
            ofs << msg << endl;
            ofs.close();
            return 1;
        }
        return 0;
    }

public:
    LARGE_INTEGER ElapsedMicroseconds;

    void Start()
    {
        QueryPerformanceFrequency(&Frequency);
        QueryPerformanceCounter(&StartingTime);
    }

    void Stop()
    {
        QueryPerformanceCounter(&EndingTime);
        ElapsedMicroseconds.QuadPart = EndingTime.QuadPart - StartingTime.QuadPart;
        ElapsedMicroseconds.QuadPart *= 1000000;
        ElapsedMicroseconds.QuadPart /= Frequency.QuadPart;
    }

    void LogElapsedVerb(std::string verb)
    {
        char elapsed[255];
        sprintf_s(elapsed, "%d", ElapsedMicroseconds);
        verb += elapsed;
        WriteLog(verb.c_str());
    }
    
};
