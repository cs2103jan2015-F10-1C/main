#include "ExecuteDropDown.h"
#include <assert.h>

ExecuteDropDown::ExecuteDropDown(UserTask* task) {
	_task = task;
}


ExecuteDropDown::~ExecuteDropDown()
{
}

string ExecuteDropDown::execute(Storage& _storage, ExtDataBase extdb, vector<list<StickyNote>::iterator>& _allItems) {

	string userInput = _task->getRemaining();
	assert(checkingOption(userInput) == true);

	if (checkingOption(userInput)){
		return displayAllTask(_storage, _allItems);
	}
	else{
		return "";
	}
}

string ExecuteDropDown::undo() {
	return "";
}

bool ExecuteDropDown::checkingOption(string userInput) {
	return userInput == "Display All Tasks";
}

string ExecuteDropDown::displayAllTask(Storage& _storage, vector<list<StickyNote>::iterator>& _allItems){
	ostringstream oss;

	_allItems.clear();

	vector<list<StickyNote>::iterator> taskToday;
	vector<list<StickyNote>::iterator> taskTmr;
	vector<list<StickyNote>::iterator> unbounded;


	getTodayTasks(taskToday, _storage);
	getTomorrowTasks(taskTmr, _storage);
	getUnboundedTasks(unbounded, _storage);

	vector<list<StickyNote>::iterator>::iterator iter;

	// today tasks
		iter = taskToday.begin();
		int size = taskToday.size();
		vector<vector<list<StickyNote>::iterator>::iterator> toDelete;

		for (size_t i = 0; i < size; i++, iter++) {
			if (taskToday[i]->getPriority() == "high" && taskToday[i]->getStatus() != "cleared") {
				_allItems.push_back(taskToday[i]);
				toDelete.push_back(iter);
			}
		}
		while (!toDelete.empty()) {
				taskToday.erase(toDelete.back());
				toDelete.pop_back();
		}

	while (!taskToday.empty()) {
		if (taskToday.back()->getStatus() != "cleared") {
			_allItems.push_back(taskToday.back());
			taskToday.pop_back();
		}
		else {
			taskToday.pop_back();
		}
	}

	// tomorrow tasks
		iter = taskTmr.begin();
		size = taskTmr.size();

		for (size_t i = 0; i < size; i++, iter++) {
			if (taskTmr[i]->getPriority() == "high" && taskTmr[i]->getStatus() != "cleared") {
				if (taskTmr.back()->getStatus() != "cleared") {
					_allItems.push_back(taskTmr[i]);
					toDelete.push_back(iter);
				}
				else {
					taskTmr.pop_back();
				}
			}
		}
		while (!toDelete.empty()) {
			taskTmr.erase(toDelete.back());
			toDelete.pop_back();
		}

	while (!taskTmr.empty()) {
		if (taskTmr.back()->getStatus() != "cleared") {
			_allItems.push_back(taskTmr.back());
			taskTmr.pop_back();
		}
		else {
			taskTmr.pop_back();
		}
	}

	// unbounded tasks
	while (!unbounded.empty()) {
		if (unbounded.back()->getStatus() != "cleared") {
			_allItems.push_back(unbounded.back());
			unbounded.pop_back();
		}
		else {
			unbounded.pop_back();
		}
	
	}

	Date date;
	int counter = 1;

		oss << "TODAY: " << "\r\n";

		for (size_t i = 0; i < _allItems.size(); i++) {
			if ((_allItems[i]->getDate() == date.getTodayDate()) && _allItems[i]->getStatus() != "cleared") {
				oss << counter << ". " << _storage.oneTaskInfoTypeOne(_allItems[i]);
				counter++;
			}
		}


		oss << "\r\n" << "TOMORROW: " << "\r\n";

		for (size_t i = 0; i < _allItems.size(); i++) {
			if ((_allItems[i]->getDate() == date.getTomorrowDate()) && _allItems[i]->getStatus() != "cleared") {
				oss << counter << ". " << _storage.oneTaskInfoTypeOne(_allItems[i]);
				counter++;
			}
		}

		oss << "\r\n" << "UNBOUNDED: " << "\r\n";

		for (size_t i = 0; i < _allItems.size(); i++) {
			if ((_allItems[i]->getDate() == "unbounded event") && _allItems[i]->getStatus() != "cleared") {
				oss << counter << ". " << _storage.oneTaskInfoTypeOne(_allItems[i]);
				counter++;
			}
		}
	
	


	return oss.str();
}



void ExecuteDropDown::getTodayTasks(vector<list<StickyNote>::iterator>& taskToday, Storage& _storage){
	Date date;
	string currentDate = date.getTodayDate();
	list<StickyNote>::iterator iter = _storage.getIter();
	size_t _size = _storage.getSize();

	for (size_t i = 0; i < _size; i++, iter++){
		if (iter->getDate() == currentDate){
			taskToday.push_back(iter);
		}
	}

}

void ExecuteDropDown::getTomorrowTasks(vector<list<StickyNote>::iterator>& taskTmr, Storage& _storage){
	Date date;
	string tomorrow = date.getTomorrowDate();
	list<StickyNote>::iterator iter = _storage.getIter();
	size_t _size = _storage.getSize();

	for (size_t i = 0; i < _size; i++, iter++){
		if (iter->getDate() == tomorrow){
			taskTmr.push_back(iter);
		}
	}

}


void ExecuteDropDown::getUnboundedTasks(vector<list<StickyNote>::iterator>& unbounded, Storage& _storage){
	
	list<StickyNote>::iterator iter = _storage.getIter();
	size_t _size = _storage.getSize();

	for (size_t i = 0; i < _size; i++, iter++){
		if (iter->getDate() == "unbounded event"){
			unbounded.push_back(iter);
		}
	}

}