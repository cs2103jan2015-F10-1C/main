#include "ExecuteEdit.h"
#include <sstream>



ExecuteEdit::ExecuteEdit(UserTask* task) {
	_task = task;
}


ExecuteEdit::~ExecuteEdit()
{
}

string ExecuteEdit::execute(Storage& _storage, ExtDataBase extdb, vector<list<StickyNote>::iterator>& _allItems) {
	
	string toEdit = _task->getRemaining();
	if (toEdit == ""){
		return MESSAGE_WRONG_INDEX;
	}

	bool isUndo = false;
	string type = toEdit.substr(0, 4);
	if (type == "undo") {
		isUndo = true;
		toEdit = toEdit.substr(5);
	}

	string editIndex;
	bool isFound = false;

	int pos = toEdit.find_first_of(" ", 0);
	editIndex = toEdit.substr(0, pos);

	for (size_t i = 0; i < editIndex.size(); i++) {
		if (editIndex[i] < '0' || editIndex[i] > '9') {
			return MESSAGE_WRONG_INDEX;
		}
	}

	list<StickyNote>::iterator iter;
	
	if (editIndex.size() == 6) {
		
		iter = _storage.getIter();
		for (size_t i = 0; i < _storage.getSize(); i++, iter++) {
			if (iter->getIndex() == editIndex) {
				isFound = true;
				break;
			}
		}
	}
	else {
		int forEdit = atoi(editIndex.c_str());
		forEdit--;

		if (forEdit < 0 || forEdit >= _allItems.size()) {
			return MESSAGE_WRONG_INDEX;
		}
		isFound = true;
		iter = _allItems[forEdit];
	}

	toEdit = toEdit.substr(pos+1);

	string details = "";
	string date = "";
	string time = "";
	string priority;
	string index = "";
	string category = "";
	bool isADeadline = false;
	Date checkDate;
	Standardise item;

	if (isFound){
		string undo;
		undo = _storage.oneTaskInfoTypeTwo(iter);

		HandleInput handleInput;

		handleInput.handle(toEdit, details, date, time, priority, index, category, isADeadline, _storage);

		bool changeOccur = false;

		if (details != "" && details != iter->getDetails()) {
			iter->setDetails(details);
			changeOccur = true;
		}

		if (time != "" && time != "All day event" && time != iter->getTime()) {
			time = item.standardiseTime(time);
			if (date == "" && time != "All day event") {
				if (iter->getDate() == "unbounded event")
					date = checkDate.getTodayDate();
			}
			iter->setTime(time);
			int st;
			int et;
			checkDate.setTaskTime(st, et, time, category);
			iter->setStartTime(st);
			iter->setEndTime(et);
			changeOccur = true;
		}

		if (date != "" && date != "unbounded event" && date != iter->getDate()) {
			date = item.standardiseDate(date);
			iter->setDate(date);
			changeOccur = true;
		}

		if (priority != "" && priority != iter->getPriority()) {
			if (priority == "none"){
				priority == "";
			}
			iter->setPriority(priority);
			changeOccur = true;
		}

		category = item.standardiseCategory(isADeadline, time);
		if (category != iter->getCategory()) {
			iter->setCategory(category);
			changeOccur = true;
		}

		_storage.findClashes(iter);


		index = iter->getIndex();

		if (!isUndo) {
			undo = "edit undo " + index + " " + undo;
			_undoEdit.push(undo);
		}



		if (changeOccur) {
			return "The Task have been edited successfully to\r\n" + _storage.oneTaskInfoTypeOne(iter);
		}
		else {
			return MESSAGE_ERROR;
		}
	}
	else {
		return MESSAGE_WRONG_INDEX;
	}
}

string ExecuteEdit::undo() {

	string undoEdit;
	undoEdit = _undoEdit.top();
	_undoEdit.pop();
	return undoEdit;
}