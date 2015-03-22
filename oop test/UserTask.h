#pragma once
#include "Global.h"

class UserTask
{
private:
	COMMAND _command;
	string _remaining;
public:
	UserTask();
	~UserTask();
	void setCommand(COMMAND);
	COMMAND getCommand();
	void setRemaining(string);
	string getRemaining();
};

