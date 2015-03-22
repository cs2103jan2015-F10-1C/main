#pragma once
#include "Global.h"
#include "UserTask.h"

class Parser
{
private:
	UserTask* _task;

public:
	Parser();
	~Parser();
	UserTask* parse(string);
};

