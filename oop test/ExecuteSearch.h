#pragma once
#include "Global.h"
#include "Executor.h"
#include "Storage.h"
#include "UserTask.h"
#include "ExtDataBase.h"

class ExecuteSearch : public Executor {
private: 
	UserTask* _task;

public:
	ExecuteSearch(UserTask*);
	~ExecuteSearch();

	string execute(Storage&, ExtDataBase, vector<list<StickyNote>::iterator>& );
	string undo();

	bool haveThisInfo(string, list<StickyNote>::iterator);
	bool compareStrings(string, string);

};

