#pragma once
#include "Global.h"
#include "ExtDataBase.h"
#include "Executor.h"
#include "Storage.h"
#include "UserTask.h"

class ExecuteMark : public Executor {
private:
	UserTask* _task;
public:
	ExecuteMark(UserTask*);
	~ExecuteMark();

	string execute(Storage&, ExtDataBase);
	string undo();
};

