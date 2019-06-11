#include "TimeUtils.h"

TimeUtils::TimeUtils()
{
}


TimeUtils::~TimeUtils()
{
}

void TimeUtils::start()
{
	startTime = high_resolution_clock::now();
}

void TimeUtils::stop()
{
	endTime= high_resolution_clock::now();
}

long TimeUtils::getDuration()
{
	return (long)duration_cast<nanoseconds>(endTime - startTime).count();
}
