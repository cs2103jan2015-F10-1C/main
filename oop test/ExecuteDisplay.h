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

	string execute(Storage&, ExtDataBase, vector<list<StickyNote>::iterator>&);
	string undo();

	void getTodayTasks(vector<list<StickyNote>::iterator>&, Storage&);
	void getTomorrowTasks(vector<list<StickyNote>::iterator>&, Storage&);
	void getUnboundedTasks(vector<list<StickyNote>::iterator>&, Storage&);
	void getDay3Tasks(vector<list<StickyNote>::iterator>&, Storage&);
	void getDay4Tasks(vector<list<StickyNote>::iterator>&, Storage&);
	void getDay5Tasks(vector<list<StickyNote>::iterator>&, Storage&);
	void getDay6Tasks(vector<list<StickyNote>::iterator>&, Storage&);
	void getDay7Tasks(vector<list<StickyNote>::iterator>&, Storage&);
	void pushToAllItem(vector<list<StickyNote>::iterator>&, vector<list<StickyNote>::iterator>&);
};

