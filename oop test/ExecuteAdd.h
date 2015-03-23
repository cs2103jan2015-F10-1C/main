#pragma once
#include "Global.h"
#include "Executor.h"
#include "Storage.h"
#include "StickyNote.h"
#include "UserTask.h"
#include "Standardise.h"
#include "Date.h"
#include "ExtDataBase.h"

class ExecuteAdd : public Executor {
private:
	UserTask* _task;
	stack<string> _undoAdd;

public:
	ExecuteAdd(UserTask*);
	~ExecuteAdd();

	string execute(Storage&, ExtDataBase);
	string undo();

	string getIndex(string, Storage);
	bool isSpecialDetail(string);
	bool isPriority(string);
	bool isTime(string);
	bool isBuffer(string);
	bool isDeadline(string);
};

