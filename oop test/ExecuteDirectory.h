#pragma once
#include "Global.h"
#include "ExtDataBase.h"
#include "Storage.h"
#include "Executor.h"
#include "UserTask.h"

class ExecuteDirectory : public Executor {
private:
	UserTask* _task;
	stack<string> _undoDirectory;
public:
	ExecuteDirectory(UserTask*);
	~ExecuteDirectory();

	string execute(Storage&, ExtDataBase);
	string undo();
};

