#pragma once
#include <time.h>
#include <string>
#include <ctime>
#include <sstream>
using namespace std;

class CurrentDate
{
private:
	string _CurrentDate;

public:
	CurrentDate();
	~CurrentDate();
	string getCurrentDate();
};

