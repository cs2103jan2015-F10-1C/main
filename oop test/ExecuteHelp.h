#pragma once
#include "Global.h"
#include "Executor.h"
#include "UserTask.h"
#include "ExtDataBase.h"

class ExecuteHelp : public Executor {
private:
	UserTask* _task;
public:
	ExecuteHelp(UserTask*);
	~ExecuteHelp();

	string execute(Storage&, ExtDataBase);
	string undo();
};

