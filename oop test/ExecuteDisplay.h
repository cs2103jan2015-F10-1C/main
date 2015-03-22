#pragma once
#include "Global.h"
#include "Executor.h"
#include "Storage.h"
#include "UserTask.h"
#include "Standardise.h"
#include "Date.h"
#include "ExtDataBase.h"

class ExecuteDisplay: public Executor {
private:
	UserTask* _task;
public:
	ExecuteDisplay(UserTask*);
	~ExecuteDisplay();

	string execute(Storage&, ExtDataBase);
	string undo();
};

