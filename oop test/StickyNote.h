#pragma once
#include "Global.h"


class StickyNote
{
private:

		string _details = "";
		string _date = "";
		string _time = "";
		string _priority = "";
		string _index = "";

public:
	StickyNote(void);
	~StickyNote(void);
	void setEverything(string, string, string, string, string);
	string getDetails();
	string getDate();
	string getTime();
	string getPriority();
	string getIndex();
	void setDetails(string);
	void setDate(string);
	void setTime(string);
	void setPriority(string);
};

