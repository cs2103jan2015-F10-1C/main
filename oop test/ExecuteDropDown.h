#pragma once
#include "Global.h"
#include "Executor.h"
#include "Storage.h"
#include "UserTask.h"
#include "Standardise.h"
#include "Date.h"
#include "ExtDataBase.h"
#include <assert.h>

class ExecuteDropDown : public Executor {
private:
	UserTask* _task;
	
public:
	ExecuteDropDown(UserTask*);
	~ExecuteDropDown();

	string execute(Storage&, ExtDataBase, vector<list<StickyNote>::iterator>&, bool&);
	string undo();
	bool checkingOption(string);

	string displayAllTask(Storage&, vector<list<StickyNote>::iterator>&);

	void getTodayTasks(vector<list<StickyNote>::iterator>&, Storage&);
	void getTomorrowTasks(vector<list<StickyNote>::iterator>&, Storage&);
	void getUnboundedTasks(vector<list<StickyNote>::iterator>&, Storage&);


};

