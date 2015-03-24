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

	string execute(Storage&, ExtDataBase);
	string undo();
	bool checkingOption(string);
	string displayAllTask(Storage&);
	string getTodayTask(Storage&);
	string getTodayDate();
	string getAllInfoOfOneTask(list<StickyNote>::iterator);
	string sortTasksByDate(Storage&);
	void getFutureTasks(vector<list<StickyNote>::iterator>&, Storage&);
	string sortTasksPriority(Storage&);
	string getUnboundedTasks(Storage&);

	struct compareTwoTasksByDay{
		inline bool operator()(const list<StickyNote>::iterator lhs, const list<StickyNote>::iterator rhs) {
			return lhs->getDay() < rhs->getDay();
		}
	};
};

