#include "ExecuteAdd.h"


ExecuteAdd::ExecuteAdd(UserTask* task) {
	_task = task;
}


ExecuteAdd::~ExecuteAdd()
{
}

string ExecuteAdd::execute(Storage& _storage, ExtDataBase extdb) {

	string userInput = _task->getRemaining();

	istringstream iss(userInput);
	string extract;
	string buffer;
	string details;
	string date;
	string time;
	string priority;
	string index;
	Date checkDate;

	while (iss) {


		iss >> extract;

		if (!iss) {
			break;
		}

		if (isSpecialDetail(extract)) { // used to find details enclosed with " "
			if (!buffer.empty()) {
				if (details.empty()) {
					details = buffer;
				}
				else {
					details = details + " " + buffer;
				}
			}
			buffer.clear();

			extract = extract.substr(1); // removes the " at start of word

			if (extract[extract.length() - 1] != '"') {
				do{
					if (details.empty()) {
						details = extract;
					}
					else {
						details = details + " " + extract;
					}
					iss >> extract;
				} while (extract[extract.length() - 1] != '"');
			}

			extract = extract.substr(0, extract.length() - 1); // remove the final "
			details = details + " " + extract;
		}
		else if (isPriority(extract)) {
			priority = extract.substr(1); // to remove "-"
		}
		else if (isTime(extract)) {
			if (time.empty()) {
				time = extract;
			}
			else {
				if (buffer == "-" || buffer == "to") {
					time = time + "-" + extract;
				}
			}
			buffer.clear();
		}
		else if (checkDate.isDate1(extract)) { // date1 means there are more things to extract adjacent to it, either before or after. 
			if (!buffer.empty()) {
				date = buffer + " " + extract;
			}
			else {
				date = extract;
				iss >> extract; // take in next item
				date = date + " " + extract;
			}
			buffer.clear();
		}
		else if (checkDate.isDate2(extract)) { // date2 identifies date terms which do not need other adjacent terms
			if (buffer == "on") {
				buffer.clear();
			}
			if (!buffer.empty()) {
				if (buffer == "this" || buffer == "coming" || buffer == "this coming") {
					date = "this " + extract;
				}
				else if (buffer == "next") {
					date = "next " + extract;
				}
			}
			else {
				date = extract;
			}
			buffer.clear();
		}
		else if (isBuffer(extract)) {

			if (buffer.empty()) {
				buffer = extract;
			}
			else {
				buffer = buffer + " " + extract;
			}
		}
		else {
			if (!buffer.empty()) {
				details = details + " " + buffer;
				buffer.clear();
			}
			if (details.empty()) {
				details = extract;
			}
			else {
				details = details + " " + extract;
			}
		}
	} // end while(iss)

	Standardise item;
	date = item.standardiseDate(date);
	time = item.standardiseTime(time);
	index = getIndex(date, _storage);


	StickyNote note;
	note.setEverything(details, date, time, priority, index);
	string result = _storage.addNewNote(note);

	string undo;
	undo = "delete " + index;
	_undoAdd.push(undo); 

	return result;
}

string ExecuteAdd::getIndex(string date, Storage _storage) {

	string defaultIndex = "0000";
	string returnIndex = "";
	int counter = 0;
	bool noRepeats = false;


	counter = _storage.getSameDateCount(date);

	while (noRepeats == false) {
		// if task is unbounded, i.e. no date
		if (date == "unbounded event") {
			if (counter < 10) {
				returnIndex = defaultIndex + "0" + to_string(counter);
			}
			else {
				returnIndex = defaultIndex + to_string(counter);
			}
		}
		else { // a date exists and should be in standard form i.e. 3/3

			int pos = date.find('/');
			string temp = "";

			// assert pos
			if (pos > 0) {
				// extract day
				temp = date.substr(0, pos);
				if (temp.size() == 1) {
					returnIndex = "0";
				}
				returnIndex = returnIndex + temp;

				// extract month
				temp = date.substr(pos + 1);
				if (temp.size() == 1) {
					returnIndex = returnIndex + "0";
				}
				returnIndex = returnIndex + temp;

				// add in counter
				if (counter < 10) {
					returnIndex = returnIndex + "0" + to_string(counter);
				}
				else {
					returnIndex = returnIndex + to_string(counter);
				}
			}
		}
		noRepeats = _storage.noRepeatIndexCount(returnIndex);

		if (noRepeats == false) {
			counter++;
			returnIndex == "";
		}
	} // end noRepeat while loop

	return returnIndex;

}

bool ExecuteAdd::isSpecialDetail(string str) {

	if (str[0] == '"') {
		return true;
	}
	return false;
}

bool ExecuteAdd::isPriority(string str) {

	if (str == "-high" || str == "-mid" || str == "-low") {
		return true;
	}
	return false;
}

bool ExecuteAdd::isTime(string str) {

	string timeKey[3] = { ":", "am", "pm" };
	int pos = -1;

	for (size_t i = 0; i < 3; i++) {
		pos = str.find(timeKey[i]);
		if (pos > 0) {
			if (str[pos - 1] >= '0' && str[pos - 1] <= '9') { // meaning that there should be an integer present before the delimiter.
				return true;
			}
		}

	}
	return false;
}


bool ExecuteAdd::isBuffer(string str) {

	string bufferKey[18] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "at", "on", "-", "from", "to", "this", "coming", "next" };
	int pos = -1;

	for (size_t i = 0; i < 18; i++) {
		pos = str.find(bufferKey[i]);
		if (pos == 0) {
			return true;
		}
	}
	return false;
}

string ExecuteAdd::undo() {

	string undoAdd;
	undoAdd = _undoAdd.top();
	_undoAdd.pop();
	return undoAdd;
}