#include "ExecuteAdd.h"


ExecuteAdd::ExecuteAdd(UserTask* task) {
	_task = task;
}


ExecuteAdd::~ExecuteAdd()
{
}

string ExecuteAdd::execute(Storage& _storage, ExtDataBase extdb, vector<list<StickyNote>::iterator>& _allItems, bool& successful) {

	string userInput = _task->getRemaining();

	if (userInput.empty()) {
		successful = false;
		return MESSAGE_ERROR;
	}

	string details="";
	string date = "";
	string time = "";
	string priority = "";
	string index = "";
	string category = "";
	HandleInput handleInput;
	bool isADeadline = false;
	bool isConventionalDate = false;
	bool validDate = false;
	Date checkDate;

	handleInput.handle(userInput, details, date, time, priority, index, category, isADeadline, _storage);

	Standardise item;

	time = item.standardiseTime(time);

	if (!item.verifyValidTime(time)){
		successful = false;
		return MESSAGE_INVALID_TIME;
	}

	if (date != ""){
		validDate = checkDate.verifyValidDate(date, isConventionalDate);
	}

	if (isConventionalDate && !validDate){
		successful = false;
		return MESSAGE_INVALID_DATE;
	}

	date = item.standardiseDate(date);
	if (date == "unbounded event" && time != "All day event") {
		date = checkDate.getTodayDate();
	}
	category = item.standardiseCategory(isADeadline, time);
	index = handleInput.getIndex(date, _storage);

	StickyNote note;
	note.setEverything(details, date, time, priority, index);
	note.setCategory(category);
	note.setStatus("incomplete");
	int st;
	int et;
	checkDate.setTaskTime(st, et, time, category);
	note.setStartTime(st);
	note.setEndTime(et);
	string result = _storage.addNewNote(note);

	string undo;
	undo = "delete " + index;
	_undoAdd.push(undo);

	successful = true;
	return result;
}


string ExecuteAdd::undo() {

	string undoAdd;
	undoAdd = _undoAdd.top();
	_undoAdd.pop();
	return undoAdd;
}
