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
	string type = toEdit.substr(0, 5); 
	if (type == "undo ") {
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
	Date checkDate;
	Standardise item;
	
	
	//Standardise standard;
	//Date date;

	for (size_t i = 0; i < _size; i++, iter++) {
		if (iter->getIndex() == editIndex) {

			string undo;
			undo = _storage.oneTaskInfoTypeTwo(iter);

			HandleInput handleInput;

			handleInput.handle(toEdit, details, date, time, priority, index, category, isADeadline, _storage);

			bool changeOccur = false;
			
			if (details != "" && details != iter->getDetails()) {
				iter->setDetails(details);
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
				}
				changeOccur = true;
			}

			if (time != "" && time != "All day event" && time != iter->getTime()) {
				time = item.standardiseTime(time);
				if (date == "unbounded event" && time != "All day event") {
					date = checkDate.getTodayDate();
				}
				iter->setTime(time);
				iter->setDate(date);
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

			if (!isUndo) {
				undo = "edit " + editIndex + " undo " + undo;
				_undoEdit.push(undo);
			}
			
			if (changeOccur) {
				return _storage.oneTaskInfoTypeOne(iter);
			}
			else {
				return MESSAGE_ERROR;
			}

			/*
			string undo;
			undo = "edit " + editIndex + " des \"" + iter->getDetails() + "\"" + " date " + iter->getDate() + " time " + iter->getTime() + " prior " + iter->getPriority();
			_undoEdit.push(undo);

			string change = toEdit.substr(6);
			//change = change.substr(0, change.size() - 2);
			//string category;
			istringstream iss(change);
			string extract;
			string input;
			string con;
			bool changeOccured;

			iss >> extract;
			while (iss) {
				
				if (!iss) {
					break;
				}

				if (isKeyWord(extract)) {

					iss >> input;
					while (!isKeyWord(input) && iss) {
						if (con.empty()) {
							con = input;
						}
						else {
							con = con + " " + input;
						}
						iss >> input;
					}

					if (extract == "des") {
						iter->setDetails(con);
						changeOccured = true;
					}
					else if (extract == "date") {
						con = standard.standardiseDate(con);
						iter->setDate(con);
						changeOccured = true; 
					}
					else if (extract == "time") {
						con = standard.standardiseTime(con);
						iter->setTime(con);
						if (iter->getDate() == "" || iter->getDate() == "unbounded event") {
							iter->setDate(date.getTodayDate());
						}
						changeOccured = true;

					}
					else if (extract == "prior") {
						if (con == "high" || con == "low" || con == "mid" || con == "") {
							iter->setPriority(con);
							changeOccured = true;
						}

					}
				}

				extract = input;
				input.clear();
				con.clear();

			} // end while iss.
			if (changeOccured) {
				return _storage.oneTaskInfoTypeOne(iter);
			}
			else {
				return MESSAGE_ERROR;
			}
			*/
			
			
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