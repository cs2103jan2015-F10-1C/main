#include "Date.h"


Date::Date()
{
}


Date::~Date()
{
}

bool Date::isDate1(string str) {

	string monthKey[24] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec",
		"jan", "feb", "mar", "apr", "may", "jun", "jul", "aug", "sep", "oct", "nov", "dec" };
	int pos = -1;

	for (size_t i = 0; i < 24; i++) {
		pos = str.find(monthKey[i]);
		if (pos == 0) {
			return true;
		}
	}
	return false;
}

bool Date::isDate2(string str) {

	string dateKey[17] = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday",
		"monday", "tuesday", "wednesday", "thursday", "friday", "saturday", "sunday", "today", "tomorrow", "/" };
	int pos = -1;

	for (size_t i = 0; i < 17; i++) {
		pos = str.find(dateKey[i]);
		if (pos == 0) {
			return true;
		}
		else if (pos > 0 && i == 16) { // to find and ensure it is a date i.e. 11/12
			return true;
		}
	  }
	return false;
}


string Date::standardizeMonth(string month){
	stringstream ss;
	string monthKey[36] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec",
		"jan", "feb", "mar", "apr", "may", "jun", "jul", "aug", "sep", "oct", "nov", "dec",
		"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12" };
	int pos = -1;
	for (size_t i = 0; i < 36; i++) {
		if (month == monthKey[i]) {
			int value = (i+1)%12;
			if (value == 0){
				value = 12;
			}
			ss << value;
			return ss.str();
		}
	}
	
	return month;
}

bool Date::seperateDateNMonth(string& date, string& month, string all){

	string monthKey[24] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec",
		"jan", "feb", "mar", "apr", "may", "jun", "jul", "aug", "sep", "oct", "nov", "dec" };

	int pos1 = -1, pos2 = -1;
	pos1 = all.find("/");
	pos2 = all.find_first_of(' ');

	if (pos1 > 0 && pos2 < 0){
		date = all.substr(0, pos1);
		month = all.substr(pos1 + 1);
		return true;
	}
	else if (pos1 < 0 && pos2 > 0){
		string part1 = all.substr(0, pos2);
		string part2 = all.substr(pos2 + 1);
		for (size_t i = 0; i < 24; i++) {
			if (monthKey[i] == part1){
				month = part1;
				date = part2;
				return true;
			}
			else if (monthKey[i] == part2){
				month = part2;
				date = part1;
				return true;
			}
		}
	}
	else{
		return false;
	}
}

bool Date::verifyValidDate(string dateNMonth, bool& isConventionalDate){
	string date = "", month = "";

	isConventionalDate = seperateDateNMonth(date, month, dateNMonth); // Conventional date is eg. 3/3, mar 3, 3 mar. 
																		   //Next monday is not a conventional date.
	if (isConventionalDate){
		month = standardizeMonth(month);

		int intDate = atoi(date.c_str());
		int intMonth = atoi(month.c_str());
		if (intMonth < 1 || (intMonth > MONTH_PER_YEAR && intMonth!=99)){
			return false;
		}
		switch (intMonth){
		case 99:
			if (intDate == 99){
				return true;
			}
			else{
				return false;
			}
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			if (intDate >= 1 && intDate <= DAY_PER_SOLAR_MONTH_OF_31){
				return true;
			}
			else{
				return false;
			}
		case 4:
		case 6:
		case 9:
		case 11:
			if (intDate >= 1 && intDate <= DAY_PER_SOLAR_MONTH_OF_30){
				return true;
			}
			else{
				return false;
			}
		case 2:
			struct tm * timeInfo = new struct tm;
			int year = timeInfo->tm_year + 1900;
			if (year % 100 != 0 && year % 4 == 0){
				if (intDate >= 1 && intDate <= DAY_OF_FEB_IN_LEAP_YEAR){
					return true;
				}
				else{
					return false;
				}
			}
			else if (year % 100 == 0 && year % 400 == 0){
				if (intDate >= 1 && intDate <= DAY_OF_FEB_IN_LEAP_YEAR){
					return true;
				}
				else{
					return false;
				}
			}
			else{
				if (intDate >= 1 && intDate <= DAY_OF_FEB_IN_NON_LEAP_YEAR){
					return true;
				}
				else{
					return false;
				}
			}
		}
	}
	return true;
}

string Date::getTodayDate() {

	time_t rawTime;
	struct tm * timeInfo = new struct tm;

	time(&rawTime);
	localtime_s(timeInfo, &rawTime);

	int day = timeInfo->tm_mday;
	int month = timeInfo->tm_mon + 1;
	int year = timeInfo->tm_year + SYSTEM_TIME_YEAR_STARTING_POINT;
	int wDay = timeInfo->tm_wday;

	string currentDate = to_string(day) + "/" + to_string(month);
	return currentDate;
}

string Date::getTomorrowDate() {

	time_t rawTime;
	struct tm * timeInfo = new struct tm;

	time(&rawTime);
	rawTime = rawTime + SEC_PER_DAY;
	localtime_s(timeInfo, &rawTime);

	int day = timeInfo->tm_mday;
	int month = timeInfo->tm_mon + 1;
	int year = timeInfo->tm_year + SYSTEM_TIME_YEAR_STARTING_POINT;
	int wDay = timeInfo->tm_wday;

	string tomorrow = to_string(day) + "/" + to_string(month);
	Standardise standard;
	standard.standardiseDate(tomorrow);
	return tomorrow;

}

string Date::getXDaysLaterDate(int add) {

	time_t rawTime;
	struct tm * timeInfo = new struct tm;

	time(&rawTime);
	rawTime = rawTime + SEC_PER_DAY;
	localtime_s(timeInfo, &rawTime);

	int day = timeInfo->tm_mday;
	int month = timeInfo->tm_mon + 1;
	int year = timeInfo->tm_year + SYSTEM_TIME_YEAR_STARTING_POINT;
	int wDay = timeInfo->tm_wday;

	day = day + add - 1;
	string xDays = to_string(day) + "/" + to_string(month);
	Standardise standard;
	standard.standardiseDate(xDays);
	return xDays;

}


void Date::setTaskTime(int& st, int& et, string time, string category) {

	
	int posCol; 
	int posDas;

	posCol = time.find_first_of(":", 0);
	posDas = time.find_first_of("-", 0);

	if (posCol == -1 || posDas == -1) {
		st = 0;
		et = 0;
		return;
	}


	string start = time.substr(0, posCol) + time.substr(posCol + 1, posDas - (posCol + 1));
	st = atoi(start.c_str());

	posCol = time.find_first_of(":", posDas);
	string end = time.substr(posDas + 1, posCol - (posDas + 1)) + time.substr(posCol + 1);
	et = atoi(end.c_str());
	
	if (category == "Deadline") {
		et = 0;
	}
}

string Date::getDateDetails(string date) {

	time_t rawTime;
	struct tm * timeInfo = new struct tm;

	time(&rawTime);
	localtime_s(timeInfo, &rawTime);

	int currentDay = timeInfo->tm_mday;
	int currentMonth = timeInfo->tm_mon + 1;
	int currentYear = timeInfo->tm_year + SYSTEM_TIME_YEAR_STARTING_POINT;
	int currentWDay = timeInfo->tm_wday;

	if (currentWDay == 0){
		currentWDay = 7; // 7 is the position of Sunday in a week.
	}

	string wDays[DAY_PER_WEEK] = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday" };
	string months[MONTH_PER_YEAR] = { "January", "February", "March", "April", "May", "June", "July", "August", 
		"September", "October", "November", "December" };
	int daysInMthOfNonLeap[MONTH_PER_YEAR] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int daysInMthOfLeap[MONTH_PER_YEAR] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	int pos = date.find("/");
	string sDay = date.substr(0,pos);
	string sMth = date.substr(pos+1);

	int day = atoi(sDay.c_str());
	int mth = atoi(sMth.c_str());

	int diff = mth - currentMonth;

	if (diff > 0) {
		for (int i = 0; i < diff; i++) {
			if ((currentYear % 100 != 0 && currentYear % 4 == 0) || (currentYear % 100 == 0 && currentYear % 400 == 0)){
				day = day + daysInMthOfLeap[(mth - 1) + i];
			}
			else{
				day = day + daysInMthOfNonLeap[(mth - 1) + i];
			}
		}
	}

	int dayDiff = day - currentDay;


	int weekDay = ((currentWDay - 1) + (dayDiff % DAY_PER_WEEK)) % DAY_PER_WEEK;

	string returnItem = wDays[weekDay] + ", " + sDay + " " + months[mth - 1];

	return returnItem;

}
