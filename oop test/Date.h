#pragma once
#include "Global.h"
#include "Standardise.h"

class Date {
private:

public:
	Date();
	~Date();

	bool isDate1(string);
	bool isDate2(string);
	string getTodayDate();
	string getTomorrowDate();
	string getXDaysLaterDate(int);
	string getDateDetails(string);
	void setTaskTime(int&, int&, string, string);
};

