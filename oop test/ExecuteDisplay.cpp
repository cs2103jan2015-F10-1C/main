#include "ExecuteDisplay.h"
#include <sstream>


ExecuteDisplay::ExecuteDisplay(UserTask* task) {
	_task = task;
}


ExecuteDisplay::~ExecuteDisplay()
{
}
//@author A0110748J
string ExecuteDisplay::execute(Storage& _storage, ExtDataBase extdb, vector<list<StickyNote>::iterator>& _allItems, bool& successful) {

	string type = _task->getRemaining();
	
	if (type == "") {
		ostringstream oss;

		_allItems.clear();

		vector<list<StickyNote>::iterator> taskToday;
		vector<list<StickyNote>::iterator> taskTmr;
		vector<list<StickyNote>::iterator> unbounded;


		getTodayTasks(taskToday, _storage);
		getTomorrowTasks(taskTmr, _storage);
		getUnboundedTasks(unbounded, _storage);

		pushToAllItem(taskToday, _allItems);
		pushToAllItem(taskTmr, _allItems);
		pushToAllItem(unbounded, _allItems);

		// show to user

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

		successful = true;
		return oss.str();
	} // end if no specification.

	else if (type == "search") {
		ostringstream oss;
		int counter = 1;

		if (_allItems.size() == 0) {
			successful = false;
			return MESSAGE_EMPTY_SEARCH;
		}
		else {
			for (size_t i = 0; i < _allItems.size(); i++) {
				oss << counter << ". " << _storage.oneTaskInfoTypeOne(_allItems[i]);
				counter++;
			}
			successful = true;
			return oss.str();
		}
	} // end search if

	else if (type == "week") {

		ostringstream oss;

		_allItems.clear();

		vector<list<StickyNote>::iterator> day1;
		vector<list<StickyNote>::iterator> day2;
		vector<list<StickyNote>::iterator> day3;
		vector<list<StickyNote>::iterator> day4;
		vector<list<StickyNote>::iterator> day5;
		vector<list<StickyNote>::iterator> day6;
		vector<list<StickyNote>::iterator> day7;

		getTodayTasks(day1, _storage);
		getTomorrowTasks(day2, _storage);
		getDay3Tasks(day3, _storage);
		getDay4Tasks(day4, _storage);
		getDay5Tasks(day5, _storage);
		getDay6Tasks(day6, _storage);
		getDay7Tasks(day7, _storage);


		pushToAllItem(day1, _allItems);
		pushToAllItem(day2, _allItems);
		pushToAllItem(day3, _allItems);
		pushToAllItem(day4, _allItems);
		pushToAllItem(day5, _allItems);
		pushToAllItem(day6, _allItems);
		pushToAllItem(day7, _allItems);


		//show to user
		
		Date date;
		int counter = 1;
		// day 1

		oss << date.getDateDetails(date.getTodayDate()) << "\r\n";

		for (size_t i = 0; i < _allItems.size(); i++) {
			if ((_allItems[i]->getDate() == date.getTodayDate()) && _allItems[i]->getStatus() != "cleared") {
				oss << counter << ". " << _storage.oneTaskInfoTypeOne(_allItems[i]);
				counter++;
			}
		}
		// day 2

		oss << "\r\n" << date.getDateDetails(date.getTomorrowDate()) << "\r\n";

		for (size_t i = 0; i < _allItems.size(); i++) {
			if ((_allItems[i]->getDate() == date.getTomorrowDate()) && _allItems[i]->getStatus() != "cleared") {
				oss << counter << ". " << _storage.oneTaskInfoTypeOne(_allItems[i]);
				counter++;
			}
		}
		// day 3

		oss << "\r\n" << date.getDateDetails(date.getXDaysLaterDate(2)) << "\r\n";

		for (size_t i = 0; i < _allItems.size(); i++) {
			if ((_allItems[i]->getDate() == date.getXDaysLaterDate(2)) && _allItems[i]->getStatus() != "cleared") {
				oss << counter << ". " << _storage.oneTaskInfoTypeOne(_allItems[i]);
				counter++;
			}
		}
		// day 4

		oss << "\r\n" << date.getDateDetails(date.getXDaysLaterDate(3)) << "\r\n";

		for (size_t i = 0; i < _allItems.size(); i++) {
			if ((_allItems[i]->getDate() == date.getXDaysLaterDate(3)) && _allItems[i]->getStatus() != "cleared") {
				oss << counter << ". " << _storage.oneTaskInfoTypeOne(_allItems[i]);
				counter++;
			}
		}
		// day 5

		oss << "\r\n" << date.getDateDetails(date.getXDaysLaterDate(4)) << "\r\n";

		for (size_t i = 0; i < _allItems.size(); i++) {
			if ((_allItems[i]->getDate() == date.getXDaysLaterDate(4)) && _allItems[i]->getStatus() != "cleared") {
				oss << counter << ". " << _storage.oneTaskInfoTypeOne(_allItems[i]);
				counter++;
			}
		}
		//day 6

		oss << "\r\n" << date.getDateDetails(date.getXDaysLaterDate(5)) << "\r\n";

		for (size_t i = 0; i < _allItems.size(); i++) {
			if ((_allItems[i]->getDate() == date.getXDaysLaterDate(5)) && _allItems[i]->getStatus() != "cleared") {
				oss << counter << ". " << _storage.oneTaskInfoTypeOne(_allItems[i]);
				counter++;
			}
		}
		// day 7

		oss << "\r\n" << date.getDateDetails(date.getXDaysLaterDate(6)) << "\r\n";

		for (size_t i = 0; i < _allItems.size(); i++) {
			if ((_allItems[i]->getDate() == date.getXDaysLaterDate(6)) && _allItems[i]->getStatus() != "cleared") {
				oss << counter << ". " << _storage.oneTaskInfoTypeOne(_allItems[i]);
				counter++;
			}
		}
		successful = true;
		return oss.str();

	} // end week if
	else {
		successful = false;
		return MESSAGE_ERROR;
	}

}
//@author A0093863U
void ExecuteDisplay::pushToAllItem(vector<list<StickyNote>::iterator>& day, vector<list<StickyNote>::iterator>& _allItems) {

	vector<list<StickyNote>::iterator>::iterator iter;

	iter = day.begin();
	int size = day.size();
	vector<vector<list<StickyNote>::iterator>::iterator> toDelete;

	for (size_t i = 0; i < size; i++, iter++) {
		if (day[i]->getPriority() == "high" && day[i]->getStatus() != "cleared") {
			_allItems.push_back(day[i]);
			toDelete.push_back(iter);
		}
	}
	while (!toDelete.empty()) {
		day.erase(toDelete.back());
		toDelete.pop_back();
	}

	for (size_t i = 0; i < day.size(); i++) {
		if (day[i]->getStatus() != "cleared") {
			_allItems.push_back(day[i]);
		}
	}

	day.clear();

}

//@author A0108341R
void ExecuteDisplay::getTodayTasks(vector<list<StickyNote>::iterator>& taskToday, Storage& _storage){
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
//@author A0108341R
void ExecuteDisplay::getTomorrowTasks(vector<list<StickyNote>::iterator>& taskTmr, Storage& _storage){
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
//@author A0108375A
void ExecuteDisplay::getDay3Tasks(vector<list<StickyNote>::iterator>& day3, Storage& _storage) {
	Date date;
	string xDay = date.getXDaysLaterDate(2);
	list<StickyNote>::iterator iter = _storage.getIter();
	size_t _size = _storage.getSize();

	for (size_t i = 0; i < _size; i++, iter++){
		if (iter->getDate() == xDay){
			day3.push_back(iter);
		}
	}

}
//@author A0108375A
void ExecuteDisplay::getDay4Tasks(vector<list<StickyNote>::iterator>& day4, Storage& _storage) {
	Date date;
	string xDay = date.getXDaysLaterDate(3);
	list<StickyNote>::iterator iter = _storage.getIter();
	size_t _size = _storage.getSize();

	for (size_t i = 0; i < _size; i++, iter++){
		if (iter->getDate() == xDay){
			day4.push_back(iter);
		}
	}

}
//@author A0108341R
void ExecuteDisplay::getDay5Tasks(vector<list<StickyNote>::iterator>& day5, Storage& _storage) {
	Date date;
	string xDay = date.getXDaysLaterDate(4);
	list<StickyNote>::iterator iter = _storage.getIter();
	size_t _size = _storage.getSize();

	for (size_t i = 0; i < _size; i++, iter++){
		if (iter->getDate() == xDay){
			day5.push_back(iter);
		}
	}

}
//@author A0110748J
void ExecuteDisplay::getDay6Tasks(vector<list<StickyNote>::iterator>& day6, Storage& _storage) {
	Date date;
	string xDay = date.getXDaysLaterDate(5);
	list<StickyNote>::iterator iter = _storage.getIter();
	size_t _size = _storage.getSize();

	for (size_t i = 0; i < _size; i++, iter++){
		if (iter->getDate() == xDay){
			day6.push_back(iter);
		}
	}

}
//@author A0093863U
void ExecuteDisplay::getDay7Tasks(vector<list<StickyNote>::iterator>& day7, Storage& _storage) {
	Date date;
	string xDay = date.getXDaysLaterDate(6);
	list<StickyNote>::iterator iter = _storage.getIter();
	size_t _size = _storage.getSize();

	for (size_t i = 0; i < _size; i++, iter++){
		if (iter->getDate() == xDay){
			day7.push_back(iter);
		}
	}

}

//@author A0108341R
void ExecuteDisplay::getUnboundedTasks(vector<list<StickyNote>::iterator>& unbounded, Storage& _storage){

	list<StickyNote>::iterator iter = _storage.getIter();
	size_t _size = _storage.getSize();

	for (size_t i = 0; i < _size; i++, iter++){
		if (iter->getDate() == "unbounded event"){
			unbounded.push_back(iter);
		}
	}

}

string ExecuteDisplay::undo() {
	return "";
}
