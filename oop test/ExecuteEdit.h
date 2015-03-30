#pragma once
#include "Global.h"
#include "Executor.h"
#include "Storage.h"
#include "UserTask.h"
#include "Standardise.h"
#include "ExtDataBase.h"
#include "Date.h"
#include "HandleInput.h"

class ExecuteEdit : public Executor {
private:
	UserTask* _task; 
	stack<string> _undoEdit;

public:
	ExecuteEdit(UserTask*);
	~ExecuteEdit();

	string execute(Storage&, ExtDataBase, vector<list<StickyNote>::iterator>& );
	string undo();

};

