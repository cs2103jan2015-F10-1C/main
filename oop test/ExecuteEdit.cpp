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

	size_t _size = _storage.getSize();
	list<StickyNote>::iterator iter = _storage.getIter();
	Standardise standard;
	Date date;

	for (size_t i = 0; i < _size; i++, iter++) {
		if (iter->getIndex() == editIndex) {

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
			
			
			/*
			identifyChange(&category, &change);
			if (category == "des"){
				iter->setDetails(change);
				return _storage.oneTaskInfoTypeOne(iter);
			}
			else if (category == "date"){
				change = standard.standardiseDate(change);
				iter->setDate(change);
				return _storage.oneTaskInfoTypeOne(iter);
			}
			else if (category == "time"){
				change = standard.standardiseTime(change);
				iter->setTime(change);
				return _storage.oneTaskInfoTypeOne(iter);
			}
			else if (category == "prior"){
				iter->setPriority(change);
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
void ExecuteEdit::identifyChange(string* category, string* change) {

	int start = (*change).find_first_not_of(" ", 0);
	int end = (*change).find_first_of(" ", start);
	if (end < 0){
		*category = (*change).substr(start);
		*change = "";
	}
	else{
		string temp = *change;
		*category = temp.substr(start, end - start);
		int startOfChange = temp.find_first_not_of(" ", end);
		if (startOfChange < 0){
			*change = "";
		}
		else{
			*change = temp.substr(startOfChange);
		}
	}
}
*/

bool ExecuteEdit::isKeyWord(string extract) {

	if (extract == "des" || extract == "date" || extract == "time" || extract == "prior") {
		return true;
	}
	return false;

}