#include "ExecuteEdit.h"



ExecuteEdit::ExecuteEdit(UserTask* task) {
	_task = task;
}


ExecuteEdit::~ExecuteEdit()
{
}

string ExecuteEdit::execute(Storage& _storage, ExtDataBase extdb) {
	
	string toEdit = _task->getRemaining();
	string editIndex;
	if (toEdit == ""){
		return MESSAGE_WRONG_INDEX;
	}
	if (toEdit.size() > 6) {
		 editIndex = toEdit.substr(0, 6);
		for (size_t i = 0; i < editIndex.size(); i++) {
			if (editIndex[i] < '0' || editIndex[i] > '9') {
				return MESSAGE_WRONG_INDEX;
			}
		}
	}
	else {
		return MESSAGE_NO_INFO_GIVEN;
	}

	toEdit = toEdit.substr(7);
	bool isUndo = false;
	string type = toEdit.substr(0, 4); 
	if (type == "undo") {
		isUndo = true;
		toEdit = toEdit.substr(5);
	}

	size_t _size = _storage.getSize();
	list<StickyNote>::iterator iter = _storage.getIter();
	string details = "";
	string date = "";
	string time = "";
	string priority;
	string index = "";
	string category = "";
	bool isADeadline = false;
	bool indexChange = false;
	bool isUndoRec = false;
	Date checkDate;
	Standardise item;

	for (size_t i = 0; i < _size; i++, iter++) {
		if (iter->getIndex() == editIndex) {

			string undo;
			undo = _storage.oneTaskInfoTypeTwo(iter);

			HandleInput handleInput;

			details = iter->getDetails();
			date = iter->getDate();
			time = iter->getTime();
			priority = iter->getPriority();
			index = iter->getIndex();
			category = iter->getCategory();

			handleInput.handle(toEdit, details, date, time, priority, index, category, isADeadline, _storage);

			bool changeOccur = false;
			
			if (details != "" && details != iter->getDetails()) {
				iter->setDetails(details);
				changeOccur = true;
			}

			if (time != "" && time != "All day event" && time != iter->getTime()) {
				time = item.standardiseTime(time);
				if (date == "" && time != "All day event") {
					date = checkDate.getTodayDate();
				}
				iter->setTime(time);
				changeOccur = true;
			}

			if (date != "" && date != "unbounded event" && date != iter->getDate()) {
				date = item.standardiseDate(date);
				iter->setDate(date);
				index = handleInput.getIndex(date, _storage);
				iter->setIndex(index);
				if (!isUndo) {
					undo = "edit " + index + " undo " + undo;
					_undoEdit.push(undo);
					isUndoRec = true;
				}
				
				changeOccur = true;
			}

			if (priority != "" && priority != iter->getPriority()) {
				iter->setPriority(priority);
				changeOccur = true;
			}

			category = item.standardiseCategory(isADeadline, time);
			if (category != iter->getCategory()) {
				iter->setCategory(category);
				changeOccur = true;
			}

			if (!isUndoRec) {
				if (!isUndo) {
					undo = "edit " + editIndex + " undo " + undo;
					_undoEdit.push(undo);
				}
			}
			
			if (changeOccur) {
				return _storage.oneTaskInfoTypeOne(iter);
			}
			else {
				return MESSAGE_ERROR;
			}
			
		}

	}
	return MESSAGE_WRONG_INDEX;

}

string ExecuteEdit::undo() {

	string undoEdit;
	undoEdit = _undoEdit.top();
	_undoEdit.pop();
	return undoEdit;
}

/*
bool ExecuteEdit::isKeyWord(string extract) {

	if (extract == "des" || extract == "date" || extract == "time" || extract == "prior") {
		return true;
	}
	return false;

}
*/