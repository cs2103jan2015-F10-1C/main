#include "HandleInput.h"


HandleInput::HandleInput(){}


HandleInput::~HandleInput(){}

void HandleInput::handle(string userInput, string& details, string& date, string& time, string& priority, 
	string& index, string& category, bool& isADeadline, Storage& _storage) {

	istringstream iss(userInput);
	string extract;
	string buffer;
	string deadline;
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
			if (!deadline.empty()) {
				isADeadline = true;
				deadline.clear();
			}
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
			if (!deadline.empty()) {
				isADeadline = true;
				deadline.clear();
			}
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
			if (!deadline.empty()) {
				isADeadline = true;
				deadline.clear();
			}
			if (buffer == "on") {
				buffer.clear();
			}
			if (!buffer.empty()) {

				if (isComing(buffer)) {
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
		else if (isDeadline(extract)) {

			if (extract == "be" && buffer == "to" && deadline.empty()) {
				deadline = buffer + " " + extract;
				buffer.clear();
			}
			else if (extract == "be" && buffer != "to") {
				buffer = buffer + " " + extract;
			}
			else if ((extract == "by" && deadline.empty()) || (extract == "before" && deadline.empty())) {
				deadline = extract;
			}
			else if (isDeadlineProposition(extract)){

				if (isNotDeadlineKeyword(deadline)) {
					buffer = buffer + " " + extract;
				}
			}
			else {
				deadline = deadline + " " + extract;
			}
		}
		else {
			if (!buffer.empty()) {
				details = details + " " + buffer;
				buffer.clear();
			}
			if (!deadline.empty()) {
				details = details + " " + deadline;
				deadline.clear();
			}
			if (details.empty()) {
				details = extract;
			}
			else {
				details = details + " " + extract;
			}
		}
	} // end while(iss)

	int startingPos = details.find_first_not_of(" ");
	if (startingPos >= 0){
		details = details.substr(startingPos);
	}
}


string HandleInput::getIndex(string date, Storage _storage) {

	string defaultIndex = "0000";
	string returnIndex = "";
	int numberOfTask = 0;
	bool noRepeats = false;


	numberOfTask = _storage.getSameDateCount(date);

	while (noRepeats == false) {
		// if task is unbounded, i.e. no date
		if (date == "unbounded event") {
			if (numberOfTask < 10) {
				returnIndex = defaultIndex + "0" + to_string(numberOfTask);
			}
			else {
				returnIndex = defaultIndex + to_string(numberOfTask);
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
				if (numberOfTask < 10) {
					returnIndex = returnIndex + "0" + to_string(numberOfTask);
				}
				else {
					returnIndex = returnIndex + to_string(numberOfTask);
				}
			}
		}
		noRepeats = _storage.noRepeatIndexCount(returnIndex);

		if (noRepeats == false) {
			numberOfTask++;
			returnIndex == "";
		}
	} // end noRepeat while loop

	return returnIndex;

}

bool HandleInput::isSpecialDetail(string str) {

	if (str[0] == '"') {
		return true;
	}
	return false;
}

bool HandleInput::isPriority(string str) {

	if (str == "-high" || str == "-mid" || str == "-low" || str == "-none") {
		return true;
	}
	return false;
}

bool HandleInput::isTime(string str) {

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


bool HandleInput::isBuffer(string str) {

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

bool HandleInput::isDeadline(string str) {

	string deadlineKey[13] = { "be", "due", "finish", "end", "ready", "prepare", "complete", "done", "before", "by", "on", "deadline", "is" };
	int pos = -1;

	for (size_t i = 0; i < 13; i++) {
		pos = str.find(deadlineKey[i]);
		if (pos == 0) {
			return true;
		}
	}
	return false;
}

bool HandleInput::isComing(string buffer){

	bool isComing = false;
	if (buffer == "this" || buffer == "coming" || buffer == "this coming"){
		isComing = true;
	}
	return isComing;
}

bool HandleInput::isDeadlineProposition(string extract){

	bool checkWord = false;
	if (extract == "by" || extract == "on" || extract == "is" || extract == "before"){
		checkWord = true;
	}
	return checkWord;
}

bool HandleInput::isNotDeadlineKeyword(string deadline){

	bool isNotDone = false;
	if (deadline != "due" || deadline != "end" || deadline != "finish" ||
		deadline != "ready" || deadline != "deadline" || deadline != "prepare" ||
		deadline != "complete" || deadline != "done" || deadline != "finished" ||
		deadline != "prepared" || deadline != "completed"){

		isNotDone = true;
	}

	return isNotDone;
}
