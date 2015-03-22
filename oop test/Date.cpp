#include "Date.h"


Date::Date()
{
}


Date::~Date()
{
}

bool Date::isDate1(string str) {

	string dateKey[24] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec",
		"jan", "feb", "mar", "apr", "may", "jun", "july", "aug", "sep", "oct", "nov", "dec" };
	int pos = -1;

	for (size_t i = 0; i < 24; i++) {
		pos = str.find(dateKey[i]);
		if (pos == 0) {
			return true;
		}
	}
	return false;
}

bool Date::isDate2(string str) {

	string dateKey[17] = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday", "monday", "tuesday", "wednesday", "thursday",
		"friday", "saturday", "sunday", "today", "tomorrow", "/" };
	int pos = -1;

	for (size_t i = 0; i < 17; i++) {
		pos = str.find(dateKey[i]);
		if (pos == 0) {
			return true;
		}
		else if (pos > 0 && i == 16) { // to find and ensure it is a date i.e. 11/12
			if ((str[pos - 1] >= '0' && str[pos - 1] <= '9') && (str[pos + 1] >= '0' && str[pos + 1] <= '9')) {
				return true;
			}
		}
	}
	return false;
}

string Date::getTodayDate() {

	time_t rawTime;
	struct tm * timeInfo = new struct tm;

	time(&rawTime);
	localtime_s(timeInfo, &rawTime);

	int day = timeInfo->tm_mday;
	int month = timeInfo->tm_mon + 1;
	int year = timeInfo->tm_year + 1900;
	int wDay = timeInfo->tm_wday;

	string currentDate = to_string(day) + "/" + to_string(month);
	return currentDate;
}