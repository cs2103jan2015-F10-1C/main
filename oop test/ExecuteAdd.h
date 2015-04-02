#pragma once
#include "Global.h"
#include "Executor.h"
#include "Storage.h"
#include "StickyNote.h"
#include "UserTask.h"
#include "Standardise.h"
#include "Date.h"
#include "ExtDataBase.h"
#include "HandleInput.h"

class ExecuteAdd : public Executor {
private:
	UserTask* _task;
	stack<string> _undoAdd;

public:
	ExecuteAdd(UserTask*);
	~ExecuteAdd();

	string execute(Storage&, ExtDataBase, vector<list<StickyNote>::iterator>&);
	string undo();
};

