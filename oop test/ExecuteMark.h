#pragma once
#include "Global.h"
#include "ExtDataBase.h"
#include "Executor.h"
#include "Storage.h"
#include "UserTask.h"

class ExecuteMark : public Executor {
private:
	UserTask* _task;
	stack<string> _undoMark;
public:
	ExecuteMark(UserTask*);
	~ExecuteMark();

	string execute(Storage&, ExtDataBase, vector<list<StickyNote>::iterator>&, bool&);
	string undo();
};

