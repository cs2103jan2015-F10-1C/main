#include "ExecuteEdit.h"
#include <sstream>



ExecuteEdit::ExecuteEdit(UserTask* task) {
	_task = task;
}


ExecuteEdit::~ExecuteEdit()
{
}
//@author A0108341R
string ExecuteEdit::execute(Storage& _storage, ExtDataBase extdb, vector<list<StickyNote>::iterator>& _allItems, bool& successful) {
	
	string toEdit = _task->getRemaining();
	try{
		if (toEdit == ""){
			successful = false;
			throw MESSAGE_WRONG_INDEX;
		}
	}
	catch (string e){
		return e;
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
		try{
			if (editIndex[i] < '0' || editIndex[i] > '9') {
				successful = false;
				throw MESSAGE_WRONG_INDEX;
			}
		}
		catch (string e){
			return e;
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

		try{
			if (forEdit < 0 || forEdit >= _allItems.size()) {
				successful = false;
				throw MESSAGE_WRONG_INDEX;
			}
		}
		catch (string e){
			return e;
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

	try{
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

				try{
					if (!item.verifyValidTime(time)){
						successful = false;
						throw MESSAGE_INVALID_TIME;
					}
				}
				catch (string e){
					return e;
				}

				if (date == "" && time != "All day event") {
					if (iter->getDate() == "unbounded event")
						date = checkDate.getTodayDate();
				}
				iter->setTime(time);
				int sh, eh, sm, em;
				checkDate.setTaskTime(sh, eh, sm, em, time, category);
				iter->setStartTime(sh, sm);
				iter->setEndTime(eh, em);
				changeOccur = true;
			}

			if (date != "" && date != "unbounded event" && date != iter->getDate()) {
				bool isConventionalDate = false;
				bool validDate = false;
				validDate = checkDate.verifyValidDate(date, isConventionalDate);

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
			_storage.findClashes();


			index = iter->getIndex();

			if (!isUndo) {
				undo = "edit undo " + index + " " + undo;
				_undoEdit.push(undo);
			}


			try{
				if (changeOccur) {
					successful = true;
					return MESSAGE_EDIT + _storage.oneTaskInfoTypeOne(iter);
				}
				else {
					successful = false;
					throw MESSAGE_ERROR;
				}
			}
			catch (string e){
				return e;
			}
		}
		else {
			successful = false;
			throw MESSAGE_WRONG_INDEX;
		}
	}
	catch (string e){
		return e;
	}
}

string ExecuteEdit::undo() {

	string undoEdit;
	undoEdit = _undoEdit.top();
	_undoEdit.pop();
	return undoEdit;
}