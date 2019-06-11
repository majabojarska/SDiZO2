#pragma once
#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

class TimeUtils
{
public:
	TimeUtils();
	~TimeUtils();

	high_resolution_clock::time_point startTime;
	high_resolution_clock::time_point endTime;

	void start();
	void stop();
	long getDuration();
};

