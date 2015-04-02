#pragma once
#include "Global.h"
#include "Executor.h"
#include "Storage.h"
#include "UserTask.h"
#include "ExtDataBase.h"

class ExecuteDelete : public Executor {
private:
	UserTask* _task;
	bool _deleted;
	stack<string> _undoDelete;

public:
	ExecuteDelete(UserTask*);
	~ExecuteDelete();
	string execute(Storage&, ExtDataBase, vector<list<StickyNote>::iterator>& );
	string undo();
};

