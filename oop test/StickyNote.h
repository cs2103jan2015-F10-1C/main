#pragma once
#include "Global.h"


class StickyNote
{
private:
		
		string _category = "";
		string _details = "";
		string _date = "";
		string _time = "";
		string _priority = "";
		string _index = "";

		int _day = 0;
		int _month = 0;

		string _status = "";


public:
	StickyNote(void);
	~StickyNote(void);
	void setEverything(string, string, string, string, string);
	string getDetails();
	string getDate();
	string getTime();
	string getPriority();
	string getIndex();
	string getCategory();

	int getDay();
	int getMonth();
	string getStatus();

	void setCategory(string);
	void setDetails(string);
	void setDate(string);
	void setTime(string);
	void setPriority(string);
	void setIndex(string);

	void setDay(int);
	void setMonth(int);

	void setStatus(string);

};

