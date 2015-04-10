#include "CurrentDate.h"


CurrentDate::CurrentDate(void)
{
}


CurrentDate::~CurrentDate(void)
{
}
//@author A0093863U
string CurrentDate::getCurrentDate(){
	time_t rawTime;
	struct tm * timeInfo = new struct tm;

	time(&rawTime);
	localtime_s(timeInfo, &rawTime);

	int day = timeInfo->tm_mday;
	int month = timeInfo->tm_mon + 1;
	int year = timeInfo->tm_year + 1900;

	ostringstream oss;
	oss << day << "/" << month << "/" << year;
	return oss.str();
}

void CurrentDate::getCurrentTime(int& year, int& month, int& day, int& hour, int& min, int& sec){
	time_t rawTime;
	struct tm * timeInfo = new struct tm;
	time(&rawTime);
	localtime_s(timeInfo, &rawTime);
	year = timeInfo->tm_year + 1900;
	month = timeInfo->tm_mon + 1;
	day = timeInfo->tm_mday;
	hour = timeInfo->tm_hour;
	min = timeInfo->tm_min;
	sec = timeInfo->tm_sec;
	return;
}