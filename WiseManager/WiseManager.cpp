#include"WiseManager.h"
using namespace std;

const string MESSAGE_WELCOME = "Welcome to Wise Manager V0.1! \n";
const string MESSAGE_ADD = "New task has been added successfully.\n";
const string MESSAGE_ERROR = "Invalid input. \n";

const string MESSAGE_INFO_UNFOUND = "This keyword is not found. \n";
const string MESSAGE_NO_INFO_GIVEN = "There is no keyword inputed to be searched. \n";
const string MESSAGE_UNRECOGNISED_COMMAND_TYPE = "Command not recognised. Please re-input. \n";
const string MESSAGE_DISPLAY = "Displaying %s task(s)\n";
const string MESSAGE_UNRECOGNISED_DISPLAY_TYPE = "Display type not recognised. Please re-input. \n";
const string MESSAGE_DELETED = "The Task have been deleted successfully.";
const string MESSAGE_NOT_DELETED = "The Task have been not been deleted. Please Check your inputs.";
const string MESSAGE_TO_DELETE = "Please select which of the following tasks you want to delete:";
const string MESSAGE_TO_EDIT = "Please select the task number you want to edit:";
const string MESSAGE_EDIT_INSTRUCTIONS = "Enter the category (des, date, time, prior), followed by the changes:";

const string MESSAGE_DIRECTORY_CHANGED = "The saving file directory has been changed. \n";
const string MESSAGE_DIRECTORY_NOT_GIVEN = "The new directory is not given. Please re-input. \n";

const string MESSAGE_INVALID_HELP = "Desired command not detected. Please input the correct command that you need help in.";



const int ADD_TYPE = 1;
const int DELETE_TYPE = 2;
const int VIEW_TYPE = 3;
const int EDIT_TYPE = 4;
const int SEARCH_TYPE = 5;
const int DISPLAY_TYPE = 6;
const int EXIT_TYPE = 7;
const int HELP_TYPE = 8;
const int CHANGE_DIRECTORY_TYPE = 9;
const int ERROR_TYPE = -1;

WiseManager::WiseManager() {

	_tail = NULL;
	_size = 0;

};

WiseManager::~WiseManager(void) {
};

void WiseManager::initialise(ifstream* dataBaseRead, ofstream* dataBaseWrite, string fileName) {
	string taskLine;

	while (getline(*dataBaseRead, taskLine)){
		transferDataToList(taskLine);
	}
	autoSave(dataBaseWrite, fileName);
	return;
}

void WiseManager::setFileDirectory(string fileLocation, string fileNameStorage){
	_savingDirectory = fileLocation;
	ofstream storage(fileNameStorage);
	storage << _savingDirectory;
	storage.close();

	return;
}

string WiseManager::getFileDirectory(string fileNameStorage){
	ifstream storage(fileNameStorage);
	string fileDirectory;
	getline(storage, fileDirectory);
	storage.close();

	return fileDirectory;
}

void WiseManager::getStarted(ifstream* dataBaseRead, ofstream* dataBaseWrite, string fileName, string fileNameStorage) {

	cout << MESSAGE_WELCOME;

	string command;
	int* commandType = new int;
	string* outputMessage = new string("");

	while (*commandType != EXIT_TYPE) {
		cout << "command: ";
		getline(cin, command);
		executeCommand(command, dataBaseRead, dataBaseWrite, commandType, outputMessage, fileName, getFileDirectory(fileNameStorage));
	}
	return;
}

void WiseManager::printMessage(string str) {
	cout << str << endl;
}

void WiseManager::autoSave(ofstream* dataBaseWrite, string fileName){
	dataBaseWrite->close();
	dataBaseWrite->clear();
	dataBaseWrite->open(fileName);
	if (_size == 0){
		return;
	}
	Task* currentTask = _tail->next;
	for (int i = 0; i < _size; i++){
		*dataBaseWrite << getAllInfoOfOneTask2(currentTask);
		currentTask = currentTask->next;
	}
	return;
}

void WiseManager::transferDataToList(string taskLine){
	string detail = "Details: ";
	string date = "Date: ";
	string time = "Time: ";
	string priority = "Priority: ";
	int detailPosition = findPosition(detail, taskLine) + detail.size();
	int datePosition = findPosition(date, taskLine) + date.size();
	int timePosition = findPosition(time, taskLine) + time.size();
	int priorityPosition = findPosition(priority, taskLine) + priority.size();

	Task* item = new Task;
	item->details = taskLine.substr(detailPosition, findPosition(date, taskLine) - detailPosition);
	item->date = taskLine.substr(datePosition, findPosition(time, taskLine) - datePosition);
	item->time = taskLine.substr(timePosition, findPosition(priority, taskLine) - timePosition);
	item->priority = taskLine.substr(priorityPosition);

	item->details = removeSpace(item->details);
	item->date = removeSpace(item->date);
	item->time = removeSpace(item->time);
	item->priority = removeSpace(item->priority);

	if (_size == 0) {
		_tail = item;
		_tail->next = item;
		_tail->prev = item;
		_size++;
	}
	else if (_size > 0) {
		item->next = _tail->next;
		_tail->next->prev = item;
		_tail->next = item;
		item->prev = _tail;
		_tail = item;
		_size++;
	}
	return;
}

string WiseManager::removeSpace(string A){
	if (A == ""){
		return "";
	}
	else{
		A.erase(0, A.find_first_not_of(" "));
		A.erase(A.find_last_not_of(" ") + 1);
		return A;
	}
}

int WiseManager::findPosition(string target, string container){
	if (target.length()>container.length()){
		return -1;
	}
	else{
		size_t startingPosOfTarget, startingPosOfContainer, posUnderChecking;
		for (startingPosOfContainer = 0; startingPosOfContainer<container.length(); startingPosOfContainer++){
			startingPosOfTarget = 0;
			posUnderChecking = startingPosOfContainer;
			while (posUnderChecking<container.length() &&
				container[posUnderChecking] == target[startingPosOfTarget]){
				posUnderChecking++;
				startingPosOfTarget++;
			}

			if (startingPosOfTarget == target.length()){ //take note need to include the -2 of the string length to run in UI
				return startingPosOfContainer;
			}
		}
		return -1;
	}
}

void WiseManager::executeCommand(string command, ifstream* dataBaseRead, ofstream* dataBaseWrite, int* commandType, string* outputMessage, string fileName, string &newDirectory) {  // Still use return void instead of bool.
	
	bool changeDirectory = false;
	string temp="", remainingCommand="";
	int startOfCommand = command.find_first_not_of(" ", 0);
	int endOfCommand = command.find_first_of(" ", startOfCommand);
	if (endOfCommand < 0){
		command = command.substr(startOfCommand);
		remainingCommand = "";
	}
	else{
		temp = command.substr(startOfCommand, endOfCommand - startOfCommand);
		int startOfRemaining = command.find_first_not_of(" ", endOfCommand);
		if (startOfRemaining < 0){
			remainingCommand = "";
		}
		remainingCommand = command.substr(startOfRemaining);
		command = temp;
	}

	Command_Type identifiedCommand = identifyCommand(command); 
	
	switch (identifiedCommand) {

	case ADD:
		*outputMessage = addTask(remainingCommand);
		*commandType = ADD_TYPE;
		autoSave(dataBaseWrite, fileName);
		return;
	case VIEW:
	case DELETE:
		*outputMessage = deleteTask(remainingCommand);
		*commandType = DELETE_TYPE;
		autoSave(dataBaseWrite, fileName);
		return;
	case EDIT:
		*outputMessage = editTask(remainingCommand);
		cout << *outputMessage << endl;
		*commandType = EDIT_TYPE;
		autoSave(dataBaseWrite, fileName);
		return;
	case DISPLAY:
		*outputMessage = displayTask(remainingCommand);
		*commandType = DISPLAY_TYPE;
		return;
	case SEARCH:		
		*outputMessage = searchTask(remainingCommand);
		cout << *outputMessage << endl;
		*commandType = SEARCH_TYPE;
		return;
	case EXIT:
		*commandType = EXIT_TYPE;
		return;
	case DIRECTORY:
		*outputMessage = changeFileDirectory(remainingCommand, changeDirectory);
		*commandType = CHANGE_DIRECTORY_TYPE;
		if (changeDirectory){
			newDirectory = remainingCommand;
		}
	case HELP:
		*outputMessage = help(remainingCommand);
		*commandType = HELP_TYPE;
		return;
	case ERROR:
		*outputMessage = MESSAGE_UNRECOGNISED_COMMAND_TYPE;
		*commandType = ERROR_TYPE;
		return;

	}

}

WiseManager::Command_Type WiseManager::identifyCommand(string command) {
	if (command[command.length() - 2] == '\r'&&command[command.length() - 1] == '\n'){
		int commandSize = command.length() - 2;  // Ignore the "/r/n" of the string.
		for (size_t index = 0; index < commandSize; index++) {
			command[index] = tolower(command[index]);
		}
		command = command.substr(0, commandSize);  // Remove "/r/n" of the string from UI.
	}

	else{
		for (size_t index = 0; index < command.length(); index++) {
			command[index] = tolower(command[index]);
		}
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
	else if (command == "search") {
		return SEARCH;
	}
	else if (command == "exit") {
		return EXIT;
	}
	else if (command == "directory") {
		return DIRECTORY;
	}
	else if (command == "help") {
		return HELP;
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
have dinner 17:00

acceptable dates:
3/5 (dd/mm) -> 3 / 3 not acceptable
3 mar, 3 march
mar 3, march 3
today
tomorrow
days of week (mon - sun)

=============================================================*/

string WiseManager::addTask(string taskInformation) {

	if (taskInformation.empty()) {
		return MESSAGE_ERROR;
	}
	splitString(taskInformation);
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
			} while (extract[extract.length() - 1] != '"');

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

	Task* item = new Task;
	item->details = details;
	item->date = date;
	item->time = time;
	item->priority = priority;

	if (_size == 0) {
		_tail = item;
		_tail->next = item;
		_tail->prev = item; // point back to itself to be used later for circular list
		_size++;
	}
	else if (_size > 0) {
		item->next = _tail->next;
		_tail->next->prev = item;
		_tail->next = item;
		item->prev = _tail;
		_tail = item;
		_size++;
	}

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
	struct tm * timeInfo = new struct tm;

	time(&rawTime);
	localtime_s(timeInfo, &rawTime);

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
		return "unbounded event";
	}

	while (iss) {

		iss >> extract;

		if (!iss){
			break;
		}

		// case already in standardised form
		int found = -1;
		found = extract.find('/');
		if (found > 0) {
			return date;
		}

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
		return "All day event";
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
		hour_e = hour_s + 1; // create an hour long event
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

string WiseManager::displayAllTask(){
	ostringstream oss;
	Task* currentPosition = _tail->next;
	for (int i = 1; i <= _size; i++){
		oss << i << ". Details: " << currentPosition->details << "\r\n" << "Date: " << currentPosition->date << "\r\n" <<
			"Time: " << currentPosition->time << "\r\n" << "Priority: " << currentPosition->priority << "\r\n" << "\r\n";
		currentPosition = currentPosition->next;
	}
	return oss.str();
}


string WiseManager::displayTask(string displayType) {

	/*==================================================================
	Display Task used to, well obviously, display, task.
	it can take in the following inputs, or none:

	today or empty string - to display tasks only scheduled for today.
	e.g. display today

	specific date - to display task on a specific date.
	e.g. display 3 march
	display 3/3

	priority - display high / mid / low priority task.
	e.g. display high priority, display mid priority
	=================================================================*/

	ostringstream oss;
	Task* cur = _tail->next;
	int counter = 1;
	char buffer[100];

	// just in case, change everything to lower case
	for (int i = 0; i < displayType.size(); i++) {
		displayType[i] = tolower(displayType[i]);
	}

	if (displayType == "today" || displayType == "") {
		string currentDate = getTodayDate();
		sprintf_s(buffer, MESSAGE_DISPLAY.c_str(), currentDate.c_str());
		oss << buffer;
		printMessage(buffer);
		for (int i = 0; i < _size; i++) {
			if (cur->date == currentDate) {
				cout << counter << ". " << cur->details
					<< "[" << cur->time << "]" << endl;
				oss << counter << ". " << cur->details
					<< "[" << cur->time << "]" << "\r\n";
				counter++;
			}
			cur = cur->next;
		}
	}

	else if (displayType == "high priority" || displayType == "mid priority" || displayType == "low priority") {
		string extract;
		istringstream iss(displayType);
		iss >> extract;
		sprintf_s(buffer, MESSAGE_DISPLAY.c_str(), displayType.c_str());
		oss << buffer;
		printMessage(buffer);
		for (int i = 0; i < _size; i++) {
			if (cur->priority == extract) {
				cout << counter << ". " << cur->details
					<< "[" << cur->time << "]" << endl;
				oss << counter << ". " << cur->details
					<< "[" << cur->time << "]" << "\r\n";
				counter++;
			}
			cur = cur->next;
		}
	}

	else if (isDate1(displayType) || isDate2(displayType)) {
		string inputDate = standardiseDate(displayType);
		sprintf_s(buffer, MESSAGE_DISPLAY.c_str(), inputDate.c_str());
		oss << buffer;
		printMessage(buffer);
		for (int i = 0; i < _size; i++) {
			if (cur->date == inputDate) {
				cout << counter << ". " << cur->details
					<< "[" << cur->time << "]" << endl;
				oss << counter << ". " << cur->details
					<< "[" << cur->time << "]" << "\r\n";
				counter++;
			}
			cur = cur->next;
		}
	}

	else{
		return MESSAGE_UNRECOGNISED_DISPLAY_TYPE;
	}
	return oss.str();
}

void WiseManager::transferData(ofstream* dataDestination, ifstream* dataSource){
	string temp;
	while (getline(*dataSource, temp)){
		*dataDestination << temp << endl;
	}

	return;
}

bool WiseManager::compareStrings(string infoToBeSearched, string infoToBeChecked){
	if (infoToBeSearched.length()>infoToBeChecked.length()){
		return false;
	}
	else{
		size_t startingPosOfTask, startingPosOfInfo, posUnderChecking;
		for (startingPosOfTask = 0; startingPosOfTask<infoToBeChecked.length(); startingPosOfTask++){
			startingPosOfInfo = 0;
			posUnderChecking = startingPosOfTask;
			while (posUnderChecking<infoToBeChecked.length() &&
				infoToBeChecked[posUnderChecking] == infoToBeSearched[startingPosOfInfo]){
				posUnderChecking++;
				startingPosOfInfo++;
			}

			if (startingPosOfInfo == infoToBeSearched.length() - 2){ //take note need to include the -2 of the string length to run in UI
				return true;
			}
		}
		return false;
	}
}


bool WiseManager::haveThisInfo(string infoToBeSearched, Task* currentTask){
	string details, date, time, priority;
	if (currentTask->details == ""){
		details = "";
	}
	else{
		details = currentTask->details;
	}

	if (currentTask->date == "unbounded event"){
		date = "";
	}
	else{
		date = currentTask->date;
	}

	if (currentTask->time == "All day event"){
		time = "";
	}
	else{
		time = currentTask->time;
	}

	if (currentTask->priority == ""){
		priority = "";
	}
	else{
		priority = currentTask->priority;
	}

	return(compareStrings(infoToBeSearched, details) || compareStrings(infoToBeSearched, date) ||
		compareStrings(infoToBeSearched, time) || compareStrings(infoToBeSearched, priority));
}

string WiseManager::getAllInfoOfOneTask(Task* thisTask){ // This function returns all infomation about a specific task with Details/Date/Time/Priority for indication.
	ostringstream oss;
	oss << "Details: " << thisTask->details << "\r\n"
		<< "Date: " << thisTask->date << "\r\n"
		<< "Time: " << thisTask->time << "\r\n"
		<< "Priority: " << thisTask->priority << "\r\n";
	return oss.str();
}

string WiseManager::getAllInfoOfOneTask2(Task* thisTask){
	ostringstream oss;
	oss << "Details: " << thisTask->details
		<< " Date: " << thisTask->date
		<< " Time: " << thisTask->time
		<< " Priority: " << thisTask->priority << "\r\n";
	return oss.str();
}

string WiseManager::searchTask(string infoToBeSearched){
	if (infoToBeSearched == ""){
		return MESSAGE_NO_INFO_GIVEN;
	}

	bool infoIsFound = false;
	Task* currentTask = _tail->next;
	vector<Task*> tasksHaveThisInfo;
	for (int i = 0; i < _size; i++){
		if (haveThisInfo(infoToBeSearched, currentTask)){
			infoIsFound = true;
			tasksHaveThisInfo.push_back(currentTask);
		}
		currentTask = currentTask->next;
	}

	if (infoIsFound){
		ostringstream oss;
		for (int j = 0; j < tasksHaveThisInfo.size(); j++){
			oss << j + 1 << "." << getAllInfoOfOneTask(tasksHaveThisInfo[j]) << endl;
		}
		return oss.str();
	}
	else{
		return MESSAGE_INFO_UNFOUND;
	}

}

string WiseManager::deleteTask(string infoToBeDeleted){
	string rubbish;

	if (infoToBeDeleted == ""){
		return MESSAGE_NOT_DELETED;
	}
	bool canBeDeleted = false;
	Task* currentTask = _tail->next;
	vector<Task*> tasksWithInformation;
	for (int i = 0; i < _size; i++){
		if (haveThisInfo(infoToBeDeleted, currentTask)){
			canBeDeleted = true;
			tasksWithInformation.push_back(currentTask);
		}
		currentTask = currentTask->next;
	}

	if (canBeDeleted){
		vector<Task*>::iterator Iter = tasksWithInformation.begin();
		cout << MESSAGE_TO_DELETE << endl;
		for (int lineNumber = 1; Iter != tasksWithInformation.end(); Iter++, lineNumber++){
			cout << lineNumber << "." << getAllInfoOfOneTask(*Iter) << endl;
		}
		int lineToBeDeleted;
		cin >> lineToBeDeleted;
		cout << lineToBeDeleted;
		getline(cin, rubbish);
		Task* taskToDelete = _tail->next;
		while (tasksWithInformation[lineToBeDeleted - 1]->details != taskToDelete->details){
			taskToDelete = taskToDelete->next;
			cout << taskToDelete->details << endl;
		}
		taskToDelete->prev->next = taskToDelete->next;
		taskToDelete->next->prev = taskToDelete->prev;
		delete taskToDelete;
		taskToDelete = NULL;
		_size--;
		return MESSAGE_DELETED;
	}
	else{
		return MESSAGE_NOT_DELETED;
	}

}

string WiseManager::editTask(string keyword) {
	vector<Task*> matchingTasks;
	cout << showMatchingTasks(&matchingTasks, keyword) << endl;

	cout << MESSAGE_TO_EDIT << endl;
	int taskNum;
	cin >> taskNum;

	cout << getAllInfoOfOneTask(matchingTasks[taskNum - 1]) << endl;
	Task* currentTask = matchingTasks[taskNum - 1];
	Task* taskPositionInList = _tail->next;
	bool changeIsDone = false;

	cout << MESSAGE_EDIT_INSTRUCTIONS << endl;
	string rubbish, change;
	getline(cin, rubbish);  //get rid of the 'enter'
	getline(cin, change);

	string category;
	identifyChange(&category, &change);

	for (int i = 0; i < _size && !changeIsDone; i++){
		if (isSameTask(currentTask, taskPositionInList)){
			if (category == "des"){
				taskPositionInList->details = change;
				changeIsDone = true;
			}
			else if (category == "date"){
				change = standardiseDate(change);
				taskPositionInList->date = change;
				changeIsDone = true;
			}
			else if (category == "time"){
				change = standardiseTime(change);
				taskPositionInList->time = change;
				changeIsDone = true;
			}
			else if (category == "prior"){
				taskPositionInList->priority = change;
				changeIsDone = true;
			}
			else {
				return MESSAGE_ERROR;
			}
		}
		else{
			taskPositionInList = taskPositionInList->next;
		}
	}
	cout << "Updated specified task:" << endl;
	return getAllInfoOfOneTask(taskPositionInList);
}

bool WiseManager::isSameTask(Task* A, Task* B){
	return A->date == B->date && A->details == B->details && A->priority == B->priority && A->time == B->time;
}

void WiseManager::identifyChange(string* category, string* change)
{
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
string WiseManager::showMatchingTasks(vector<Task*> *matchingTasks, string infoToBeSearched){
	if (infoToBeSearched == ""){
		return MESSAGE_NO_INFO_GIVEN;
	}

	bool infoIsFound = false;
	Task* currentTask = _tail->next;

	for (int i = 0; i < _size; i++){
		if (haveThisInfo(infoToBeSearched, currentTask)){
			infoIsFound = true;
			(*matchingTasks).push_back(currentTask);
		}
		currentTask = currentTask->next;
	}

	if (infoIsFound){
		ostringstream oss;
		vector<Task*>::iterator browse = (*matchingTasks).begin();
		for (int j = 0; j < matchingTasks->size(); j++){
			oss << j + 1 << "." << getAllInfoOfOneTask(*browse) << "\r\n";
			browse++;
		}
		return oss.str();
	}
	else{
		return MESSAGE_INFO_UNFOUND;
	}
}

string WiseManager::changeFileDirectory(string &newDirectory, bool &changeDirectory){
	if (newDirectory == ""){
		return  MESSAGE_DIRECTORY_NOT_GIVEN;
	}
	newDirectory = newDirectory.substr(0, newDirectory.size() - 2);
	setFileDirectory(newDirectory, "fileNameStorage.txt");
	changeDirectory = true;

	return MESSAGE_DIRECTORY_CHANGED;
}

void WiseManager::getFutureTasks(vector<Task*> &futureTasks){
	Task* cur = _tail->next;

	time_t rawTime;
	struct tm * timeInfo = new struct tm;

	time(&rawTime);
	localtime_s(timeInfo, &rawTime);

	int dayNow = timeInfo->tm_mday;
	int monthNow = timeInfo->tm_mon + 1;

	for (int i = 0; i < _size; i++){
		string curTaskDate = cur->date;
		int posOfSlash = curTaskDate.find_first_of('/', 0);
		string day = curTaskDate.substr(0, posOfSlash);
		string month = curTaskDate.substr(posOfSlash + 1);
		int dayInt = atoi(day.c_str());
		int monthInt = atoi(month.c_str());
		cur->day = dayInt;
		cur->month = monthInt;
		if (monthInt>monthNow){
			futureTasks.push_back(cur);
		}
		else if (monthInt == monthNow && dayInt >= dayNow){
			futureTasks.push_back(cur);
		}
		else{
		}
		cur = cur->next;
	}

	return;
}

string WiseManager::getTodayDate(){
	time_t rawTime;
	struct tm * timeInfo = new struct tm;

	time(&rawTime);
	localtime_s(timeInfo, &rawTime);

	int day = timeInfo->tm_mday;
	int month = timeInfo->tm_mon + 1;
	int year = timeInfo->tm_year + 1900;
	int wDay = timeInfo->tm_wday;

	string currentDate = to_string(day) + "/" + to_string(month);
	return currentDate;
}


string WiseManager::getTodayTask(){
	string currentDate = getTodayDate();
	Task* cur = _tail->next;
	ostringstream oss;

	for (int i = 0; i < _size; i++){
		if (cur->date == currentDate){
			oss << getAllInfoOfOneTask(cur) << "\r\n";
		}
		cur = cur->next;
	}

	return oss.str();
}

string WiseManager::sortTasksByDate(){

	vector<Task*> futureTasks;
	getFutureTasks(futureTasks);

	ostringstream oss;

	vector<Task*> jan, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec;
	for (int i = 0; i < futureTasks.size(); i++){
		switch (futureTasks[i]->month){
		case 1:
			jan.push_back(futureTasks[i]);
			break;
		case 2:
			feb.push_back(futureTasks[i]);
			break;
		case 3:
			mar.push_back(futureTasks[i]);
			break;
		case 4:
			apr.push_back(futureTasks[i]);
			break;
		case 5:
			may.push_back(futureTasks[i]);
			break;
		case 6:
			jun.push_back(futureTasks[i]);
			break;
		case 7:
			jul.push_back(futureTasks[i]);
			break;
		case 8:
			aug.push_back(futureTasks[i]);
			break;
		case 9:
			sep.push_back(futureTasks[i]);
			break;
		case 10:
			oct.push_back(futureTasks[i]);
			break;
		case 11:
			nov.push_back(futureTasks[i]);
			break;
		case 12:
			dec.push_back(futureTasks[i]);
			break;
		default:
			break;
		}
	}

	vector<Task*> sortedFutureTasks;
	if (jan.size() > 0){
		std::sort(jan.begin(), jan.end(), compareTwoTasksByDay());
		for (int i = 0; i < jan.size(); i++){
			sortedFutureTasks.push_back(jan[i]);
		}
	}
	if (feb.size() > 0){
		std::sort(feb.begin(), feb.end(), compareTwoTasksByDay());
		for (int i = 0; i < feb.size(); i++){
			sortedFutureTasks.push_back(feb[i]);
		}
	}
	if (mar.size() > 0){
		std::sort(mar.begin(), mar.end(), compareTwoTasksByDay());
		for (int i = 0; i < mar.size(); i++){
			sortedFutureTasks.push_back(mar[i]);
		}
	}
	if (apr.size() > 0){
		std::sort(apr.begin(), apr.end(), compareTwoTasksByDay());
		for (int i = 0; i < apr.size(); i++){
			sortedFutureTasks.push_back(apr[i]);
		}
	}
	if (may.size() > 0){
		std::sort(may.begin(), may.end(), compareTwoTasksByDay());
		for (int i = 0; i < may.size(); i++){
			sortedFutureTasks.push_back(may[i]);
		}
	}
	if (jun.size() > 0){
		std::sort(jun.begin(), jun.end(), compareTwoTasksByDay());
		for (int i = 0; i < jun.size(); i++){
			sortedFutureTasks.push_back(jun[i]);
		}
	}
	if (jul.size() > 0){
		std::sort(jul.begin(), jul.end(), compareTwoTasksByDay());
		for (int i = 0; i < jul.size(); i++){
			sortedFutureTasks.push_back(jul[i]);
		}
	}
	if (aug.size() > 0){
		std::sort(aug.begin(), aug.end(), compareTwoTasksByDay());
		for (int i = 0; i < aug.size(); i++){
			sortedFutureTasks.push_back(aug[i]);
		}
	}
	if (sep.size() > 0){
		std::sort(sep.begin(), sep.end(), compareTwoTasksByDay());
		for (int i = 0; i < sep.size(); i++){
			sortedFutureTasks.push_back(sep[i]);
		}
	}
	if (oct.size() > 0){
		std::sort(oct.begin(), oct.end(), compareTwoTasksByDay());
		for (int i = 0; i < oct.size(); i++){
			sortedFutureTasks.push_back(oct[i]);
		}
	}
	if (nov.size() > 0){
		std::sort(nov.begin(), nov.end(), compareTwoTasksByDay());
		for (int i = 0; i < nov.size(); i++){
			sortedFutureTasks.push_back(nov[i]);
		}
	}
	if (dec.size() > 0){
		std::sort(dec.begin(), dec.end(), compareTwoTasksByDay());
		for (int i = 0; i < dec.size(); i++){
			sortedFutureTasks.push_back(dec[i]);
		}
	}

	for (int j = 0; j < sortedFutureTasks.size(); j++){
		oss << j + 1 << "." << getAllInfoOfOneTask(sortedFutureTasks[j]) << "\r\n";
	}

	return oss.str();
}

string WiseManager::sortTasksPriority(){
	vector<Task*> futureTasks, highPrior, midPrior, lowPrior, unbounded, sortedTasksByPrior;
	ostringstream oss;

	getFutureTasks(futureTasks);

	for (int i = 0; i <futureTasks.size(); i++){
		if (futureTasks[i]->priority[0] == 'h'){
			highPrior.push_back(futureTasks[i]);
		}
		else if (futureTasks[i]->priority[0] == 'm'){
			midPrior.push_back(futureTasks[i]);
		}
		else if (futureTasks[i]->priority[0] == 'l'){
			lowPrior.push_back(futureTasks[i]);
		}
		else{
			unbounded.push_back(futureTasks[i]);
		}
	}

	if (highPrior.size() > 0){
		for (int i = 0; i < highPrior.size(); i++){
			sortedTasksByPrior.push_back(highPrior[i]);
		}
	}
	if (midPrior.size() > 0){
		for (int i = 0; i < midPrior.size(); i++){
			sortedTasksByPrior.push_back(midPrior[i]);
		}
	}
	if (lowPrior.size() > 0){
		for (int i = 0; i < lowPrior.size(); i++){
			sortedTasksByPrior.push_back(lowPrior[i]);
		}
	}
	if (unbounded.size() > 0){
		for (int i = 0; i < unbounded.size(); i++){
			sortedTasksByPrior.push_back(unbounded[i]);
		}
	}

	for (int j = 0; j < sortedTasksByPrior.size(); j++){
		oss << j + 1 << "." << getAllInfoOfOneTask(sortedTasksByPrior[j]) << "\r\n";
	}

	return oss.str();
}


string WiseManager::getUnboundedTasks(){
	Task* cur = _tail->next;
	ostringstream oss;
	int j = 1;

	for (int i = 0; i < _size; i++){
		if (cur->date == "unbounded event"){
			oss << j << "." << getAllInfoOfOneTask(cur) << "\r\n";
			j++;
		}
		cur = cur->next;
	}

	return oss.str();
}

string WiseManager::help(string desireCommand){

	ostringstream oss;

	if (desireCommand == ""){
		return MESSAGE_INVALID_HELP;
	}

	desireCommand = desireCommand.substr(0, desireCommand.size() - 2);
	if (desireCommand == "add"){

		oss << "To use the add function, it should be input in the following format: "			<< "\r\n"
			<< "add <details of the task> date time -priority		or" << "\r\n"
			<< "add <details of the task> time date -priority		or" << "\r\n" << "\r\n"
			<< "An example of a simple add task input will be: "		<< "\r\n"
			<< "add do homework 3 march 5pm -high"						<< "\r\n"
			<< "this means adding the task do homework on 3 march at 5pm with high priority"	<< "\r\n"
			<< "\r\n"
			<< "Possible flexicommands variations for adding a task will be: "					<< "\r\n"
			<< "For the inclusion of time, indicate with :, am or pm."							<< "\r\n"
			<< "there should be no space between time and am / pm"								<< "\r\n"
			<< " e.g.have dinner 5pm"															<< "\r\n"
			<< " The following inputs are wrong: have dinner 5 pm OR have dinner 5 : 00"		<< "\r\n"
			<< "\r\n"

			<< "For the inclusion of date, do note that the inputs are in (dd/mm)"				<< "\r\n"
			<< "3 mar, 3 march, mar 3, march 3, today, tomorrow, days of week(monday - sunday)" << "\r\n"
			<< "\r\n"

			<< "For the priority of the task, it can be varied according with inputs: "			<< "\r\n"
			<< "-high represents task of high priority."										<< "\r\n"
			<< "-mid represents task of medium priority."										<< "\r\n"
			<< "-low represents task of low priority."											<< "\r\n"
			<< "\r\n"

			<< "For details with conflicting terms such as certain days in a week and am / pm, user needs to include a quotation mark" << "\r\n"
			<< "e.g.meet at \"taco tuesday\" or meet at \"cafe 3pm\" or \"high tea\""			<< "\r\n"
			<< "this is to avoid creating a task on tuesday or at 3pm."							<< "\r\n";
	}
	else if (desireCommand == "display"){

		oss << "To use the display function, it should be input in the following format: "	<< "\r\n"
			<< "1. display"																	<< "\r\n"
			<< "2. display today"															<< "\r\n"
			<< "to display task that are scheduled only for today"							<< "\r\n"
			<< "3. display tomorrow"														<< "\r\n"
			<< "to display task that are scheduled only for tomorrow"						<< "\r\n"
			<< "4. display 3 march"															<< "\r\n"
			<< "5. display 3/3"																<< "\r\n"
			<< "to display task that are scheduled only on a specific date"					<< "\r\n"
			<< "5. display high"															<< "\r\n"
			<< "to display task that are scheduled based on priority"						<< "\r\n"
			<< "\r\n";
	}
	else if (desireCommand == "search"){

		oss << "To use the search function, it should be input in the following format: "		<< "\r\n"
			<< "search <task description>"														<< "\r\n"
			<< "the function will then return the tasks with the keywords input by the user. "	<< "\r\n"
			<< "please take note the the task indexes as they will be used for delete and edit purposes" << "\r\n"
			<< "\r\n";
	}
	else if (desireCommand == "delete"){

		oss << "To use the delete function, it should be input in the following format: "	<< "\r\n"
			<< "delete <task index>"														<< "\r\n"
			<< "the function will then delete the task with the index input by the user. "	<< "\r\n"
			<< "\r\n";
	}
	else if (desireCommand == "edit"){

		oss << "To use the edit function, it should be input in the following format: "									<< "\r\n"
			<< "edit <task index> <edit target> <edit informations>"														<< "\r\n"
			<< "1. edit 1111 des physics homework"																		<< "\r\n"
			<< "2. edit 1111 date 13 march"																				<< "\r\n"
			<< "3. edit 1111 time 2pm"																					<< "\r\n"
			<< "4. edit 1111 prior low" << "\r\n"
			<< "the function will edit the task specified with the task index and then modified the categories of the task accordingly."
			<< "\r\n";
	}
	else if (desireCommand == "directory"){
		oss << "To use the edit function, it should be input in the following format: " << "\r\n"
			<< "directory <new file directory>" << "\r\n"
			<< "1. directory D:\\savefile.txt"
			<< "\r\n";
	}

	return oss.str();
}

