#include "ExecuteAdd.h"


ExecuteAdd::ExecuteAdd(UserTask* task) {
	_task = task;
}


ExecuteAdd::~ExecuteAdd()
{
}
//@author A0093863U
string ExecuteAdd::execute(Storage& _storage, ExtDataBase extdb, vector<list<StickyNote>::iterator>& _allItems, bool& successful) {

	string userInput = _task->getRemaining();
	try{
		if (userInput.empty()) {
			successful = false;
			throw MESSAGE_ERROR;
		}
	}
	catch (string e){
		return e;
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
	try{
		if (!item.verifyValidTime(time)){
			successful = false;
			throw MESSAGE_INVALID_TIME;
		}
	}
	catch (string e){
		return e;
	}

	if (date != ""){
		validDate = checkDate.verifyValidDate(date, isConventionalDate);
	}

	try{
		if (isConventionalDate && !validDate){
			successful = false;
			throw MESSAGE_INVALID_DATE;
		}
	}
	catch (string e){
		return e;
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
	int sh, sm, eh, em;
	checkDate.setTaskTime(sh, eh, sm, em, time, category);
	note.setStartTime(sh, sm);
	note.setEndTime(eh, em);
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
