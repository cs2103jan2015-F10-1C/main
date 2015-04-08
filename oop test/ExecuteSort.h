#pragma once
#include "Global.h"
#include "Storage.h"
#include "UserTask.h"
#include "ExtDataBase.h"
#include "Executor.h"

class ExecuteSort : public Executor {
private:
	UserTask* _task;

public:
	ExecuteSort(UserTask*);
	~ExecuteSort();

	string execute(Storage&, ExtDataBase, vector<list<StickyNote>::iterator>&, bool&);
	string undo();
	string getTodayDate();
	string getAllInfoOfOneTask(list<StickyNote>::iterator);
	string sortTasksByDate(Storage&);
	void getFutureTasks(vector<list<StickyNote>::iterator>&, Storage&);
	string sortTasksPriority(Storage&);

	struct compareTwoTasksByDay{
		inline bool operator()(const list<StickyNote>::iterator lhs, const list<StickyNote>::iterator rhs) {
			return lhs->getDay() < rhs->getDay();
		}
	};
};