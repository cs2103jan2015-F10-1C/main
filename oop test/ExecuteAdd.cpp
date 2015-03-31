#include "ExecuteAdd.h"


ExecuteAdd::ExecuteAdd(UserTask* task) {
	_task = task;
}


ExecuteAdd::~ExecuteAdd()
{
}

string ExecuteAdd::execute(Storage& _storage, ExtDataBase extdb, vector<list<StickyNote>::iterator>& _allItems, bool& successful) {

	string userInput = _task->getRemaining();

	string details="";
	string date = "";
	string time = "";
	string priority = "";
	string index = "";
	string category = "";
	HandleInput handleInput;
	bool isADeadline = false;
	Date checkDate;

	handleInput.handle(userInput, details, date, time, priority, index, category, isADeadline, _storage);

	Standardise item;
	time = item.standardiseTime(time);
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
	string result = _storage.addNewNote(note, successful);

	string undo;
	undo = "delete " + index;
	_undoAdd.push(undo);

	return result;
}


string ExecuteAdd::undo() {

	string undoAdd;
	undoAdd = _undoAdd.top();
	_undoAdd.pop();
	return undoAdd;
}