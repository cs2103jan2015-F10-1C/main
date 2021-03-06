#pragma once
#include "Global.h"

class Standardise
{
private: 
	string _date;
	string _time;
	string _item;
public:
	Standardise();
	~Standardise();
	string standardiseDate(string);
	string standardiseTime(string);
	string standardiseCategory(bool, string);
	bool verifyValidTime(string);
	bool checkHr(int);
	bool checkMin(int);
	bool checkCorrectSequence(int, int, int, int);
};

