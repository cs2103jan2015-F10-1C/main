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
		string _sStartTime = "";
		string _sEndTime = "";

		int _startTime = 0;
		int _endTime = 0;
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
	string getStatus();
	int getDay();
	int getMonth();
	int getStartTime();
	int getEndTime();
	string getSStartTime();
	string getSEndTime();


	void setCategory(string);
	void setDetails(string);
	void setDate(string);
	void setTime(string);
	void setPriority(string);
	void setIndex(string);
	void setStatus(string);
	void setDay(int);
	void setMonth(int);
	void setStartTime(int);
	void setEndTime(int);

	

};

