#include "WiseManager.h"


const string MESSAGE_WELCOME = "Welcome to Wise Manager V0.1! \n";
const string MESSAGE_ADD = "New task has been added successfully";

WiseManager::WiseManager() {
	
	Task* dummy = new Task;
	dummy->prev = NULL;
	dummy->next = NULL;
	_tail = dummy;
	_size = 0;

};

WiseManager::~WiseManager(void) {	
};

void WiseManager::initialise() {

	// retreive data from database file 

}

void WiseManager::getStarted() {

	cout << MESSAGE_WELCOME;
	
	string command;

	while (true) {
		cout << "command: ";
		cin >> command;
		executeCommand(command);
	}

}

void WiseManager::printMessage(string str) {
	cout << str << endl;
}

void WiseManager::executeCommand(string command) {
		
	Command_Type identifiedCommand = identifyCommand(command);

	switch (identifiedCommand) {

	case ADD:
return printMessage(addTask());
	case VIEW:
	case DELETE:
	case EDIT:
	case DISPLAY:
	case EXIT:
		return exit(0);
	case ERROR:
		cout << "Command not recognised, please re-input \n";
		return;
	}

}

WiseManager::Command_Type WiseManager::identifyCommand(string command) {

	for (size_t index = 0; index < command.length(); index++) {
		command[index] = tolower(command[index]);
	}

	if (command == "add") {
		return ADD;
	}
	else if (command == "view") {
		return VIEW;
	}
	else if (command == "delete") {
		return DELETE;
	}
	else if (command == "edit") {
		return EDIT;
	}
	else if (command == "display") {
		return DISPLAY;
	}
	else if (command == "exit") {
		return EXIT;
	}
	else
		return ERROR;

}

/*=============================================================
addTask notes:

user should include quotations around details with conflicting
terms such as days and am/pm
e.g. meet at "taco tuesday" or meet at "cafe 3pm" or "high tea"
this is to avoid creating a task on tuesday or at 3pm.

to add priority, indicate with "-"
e.g. have dinner -high/mid/low

to add time, indicate with ":", "am" or "pm".
there should be no space between time and am/pm
e.g. have dinner 5pm
NOT have dinner 5 pm
or
have dinner 5:00

acceptable dates: 
3/5 (dd/mm) -> 3 / 3 not acceptable
3 mar, 3 march
mar 3, march 3
today
tomorrow
days of week (mon - sun)

=============================================================*/

string WiseManager::addTask() {

	string userInput;

	getline(cin, userInput);
	userInput = userInput.substr(1); // remove blank space after add command
	splitString(userInput);

	return MESSAGE_ADD;

}

// splitString reads the user input word by word and attempts to
// identify each word to correctly sort it out to it's
// proper component in task struct.
void WiseManager::splitString(string userInput) {

	istringstream iss(userInput);
	string extract;
	string buffer;
	string details;
	string date;
	string time;
	string priority;


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

			do{
				if (details.empty()) {
					details = extract;
				}
				else {
					details = details + " " + extract;
				}
				iss >> extract;
			} while (extract[extract.length()-1] != '"');
			
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
		else if (isDate1(extract)) { // date1 means there are more things to extract adjacent to it, either before or after. 
			if (!buffer.empty()) {
				date = buffer + " " + extract;
			}
			else {
				date = extract;
				iss >> extract; // take in next item
				date = date + " " + extract;
			}
		} 
		else if (isDate2(extract)) { // date2 identifies date terms which do not need other adjacent terms
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

	date = standardiseDate(date);
	time = standardiseTime(time);

	cout << endl;
	cout << "details: " << details << endl;
	cout << "date: " << date << endl;
	cout << "time: " << time << endl;
	cout << "priority: " << priority << endl;
	cout << "buffer: " << buffer << endl;


}

bool WiseManager::isSpecialDetail(string str) {

	if (str[0] == '"') {
		return true;
	}
	return false;
}

bool WiseManager::isPriority(string str) {

	if (str == "-high" || str == "-mid" || str == "-low") {
		return true;
	}
	return false;
}

bool WiseManager::isTime(string str) {

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

bool WiseManager::isDate1(string str) {

	string dateKey[24] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec",
		"jan", "feb", "mar", "apr", "may", "jun", "july", "aug", "sep", "oct", "nov", "dec" };
	int pos = -1;

	for (size_t i = 0; i < 24; i++) {
		pos = str.find(dateKey[i]);
		if (pos == 0) {
			return true;
		}
	}
	return false;
}

bool WiseManager::isDate2(string str) {

	string dateKey[17] = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday", "monday", "tuesday", "wednesday", "thursday",
		"friday", "saturday", "sunday", "/", "today", "tomorrow" };
	int pos = -1;

	for (size_t i = 0; i < 17; i++) {
		pos = str.find(dateKey[i]);
		if (pos == 0) {
			return true;
		}
	}
	return false;
}

bool WiseManager::isBuffer(string str) {

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

string WiseManager::standardiseDate(string date) {


	string standardisedDate;
	string extract;
	istringstream iss(date);
	string day_extract = " ";
	string month_extract = " ";

	// get current date

	time_t rawTime;
	struct tm * timeInfo;

	time(&rawTime);
	timeInfo = localtime(&rawTime);

	int day = timeInfo->tm_mday;
	int month = timeInfo->tm_mon + 1;
	int year = timeInfo->tm_year + 1900;
	int wDay = timeInfo->tm_wday;

	// info arrays
	int daysInMth[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	string mthsInYr[12] = { "jan", "feb", "mar", "apr", "may", "jun", "jul", "aug", "sep", "oct", "nov", "dec" };
	string dayInWeek[7] = { "monday", "tuesday", "wednesday", "thursday", "friday", "saturday", "sunday" };
	string others[2] = { "today", "tomorrow" };
	string controls[2] = { "next", "this" };

	// start standardising

	if (date.empty()) {
		return "";
	}

	while (iss) {

		iss >> extract;

		if (!iss){
			break;
		}

		// case already in standardised form
	//	int found = -1;
	//	found = extract.find('/');
	//	if (found) {
	//		return date;
	//	}

		// case today or tomorrow
		for (int case1 = 0; case1 < 2; case1++) {
			if (extract == others[case1]) {
				day = day + case1;
				standardisedDate = to_string(day) + "/" + to_string(month);
				return standardisedDate;
			}
		}

		// case next / this
		for (int case2 = 0; case2 < 2; case2++) {
			if (extract == controls[case2]) {
				if (case2 == 0) { // if next
					day = day + 7;
				}
				// if this, do nothing
			}
		}

		// case day of week
		for (int case3 = 0; case3 < 7; case3++) {
			if (extract == dayInWeek[case3]) {
				int inputDay = case3 + 1; // 1: monday, 2: tuesday ... 7: sunday
				int diff; // used to calculate the number of days difference between current day and input day.
				if (inputDay <= wDay) {
					inputDay = inputDay + 7;
				}
				diff = inputDay - wDay;
				day = day + diff;
			}
		}

		// case specific date e.g. 3rd march, this function extracts the numerical day.
		for (int case4 = 0; case4 < extract.length(); case4++) {
			if (extract[case4] >= '0' && extract[case4] <= '9') {
				day_extract = day_extract + extract[case4];
			}
		}

		// case month
		extract[0] = tolower(extract[0]); // to change Month to month
		for (int case5 = 0; case5 < 12; case5++) {
			int found = -1; 
			found = extract.find(mthsInYr[case5]);
			if (found >= 0) {
				month_extract = to_string(case5 + 1);
				break;
			}
		}

	}// end while (iss)

	// check for day validity
	if (day > daysInMth[month - 1]) {
		day = day - daysInMth[month - 1];
		month++;
	}
	
	if (day_extract == " ") {
		day_extract = to_string(day);
	}
	if (month_extract == " ") {
		month_extract = to_string(month);
	}

	standardisedDate = day_extract + "/" + month_extract;

	return standardisedDate;

}

string WiseManager::standardiseTime(string inputTime) {

	if (inputTime.empty()) { // for no time input by user
		return "";
	}

	int hour_s;
	int hour_e = 00;
	int min_s = 00;
	int min_e = 00;
	string AmPm;
	string changed;
	string shour_s;
	string shour_e;
	string smin_s;
	string smin_e;

	std::string::size_type sz;

	hour_s = stoi(inputTime, &sz);
	inputTime = inputTime.substr(sz);
	if (inputTime[0] == '.' || inputTime[0] == ':') { // there exists some minutes
		inputTime = inputTime.substr(1);
		min_s = stoi(inputTime, &sz);
		inputTime = inputTime.substr(sz);
	}

	// check for any am / pm attached to start time
	if (inputTime.find("am") == 0) {
		inputTime = inputTime.substr(2); // remove am
		if (hour_s == 12) {
			hour_s = 0; // midnight = 00:00
		}
	}
	else if (inputTime.find("pm") == 0) {
		inputTime = inputTime.substr(2); // remove pm
		if (hour_s < 12) {
			hour_s = hour_s + 12;
		}
	}

	if (inputTime[0] == '-') { // end time exists
		inputTime = inputTime.substr(1);
		hour_e = stoi(inputTime, &sz);
		inputTime = inputTime.substr(sz);
		if (inputTime[0] == '.' || inputTime[0] == ':') { // there exists some miniutes
			inputTime = inputTime.substr(1);
			min_e = stoi(inputTime, &sz);
			inputTime = inputTime.substr(sz);
		}

		// check for any am / pm attached to end time
		if (inputTime.find("am") == 0) {
			inputTime = inputTime.substr(2); // remove am
			if (hour_e == 12) {
				hour_e = 0; // midnight = 00:00
			}
		}
		else if (inputTime.find("pm") == 0) {
			inputTime = inputTime.substr(2); // remove pm
			if (hour_e < 12) {
				hour_e = hour_e + 12;
			}
		}
	}
	else { // no end time found
		hour_e = hour_s++; // create an hour long event
		min_e = min_s;
	}


	// below just makes the 0's appear nicer. in output e.g. 00:00 rather than 0:0
	if (hour_s == 0) {
		shour_s = "00";
	}
	else {
		shour_s = to_string(hour_s);
	}

	if (hour_e == 0) {
		shour_e = "00";
	}
	else {
		shour_e = to_string(hour_e);
	}

	if (min_s == 0) {
		smin_s = "00";
	}
	else {
		smin_s = to_string(min_s);
	}

	if (min_e == 0) {
		smin_e = "00";
	}
	else {
		smin_e = to_string(min_e);
	}

	changed = shour_s + ":" + smin_s + "-" + shour_e + ":" + smin_e;
	
	return changed;
}
