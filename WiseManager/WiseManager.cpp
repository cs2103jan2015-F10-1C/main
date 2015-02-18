#include "WiseManager.h"


const string MESSAGE_WELCOME = "Welcome to Wisemanager V0.1! \n";
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
		return printMessage( addTask() );
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
e.g. meet at "taco tuesday" or meet at "cafe 3pm". 
this is to avoid creating a task on tuesday or at 3pm.

to add priority, indicate with "-"
e.g. have dinner -high/mid/low

to add time, indicate with ":", "am" or "pm". 
there should be no space between time and am/pm
e.g. have dinner 5pm 
	 NOT have dinner 5 pm
or 
	have dinner 5:00

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

		if (isPriority(extract)) {
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
		else if (isDate1(extract)) { // date1 means i have more things to extract adjacent to it, either before or after. 
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
			if (!buffer.empty()) {
				buffer.clear();
			}
			date = extract;
		}
		else if (isBuffer(extract)) {
			
			if (buffer == "on") {
				buffer.clear();
			}
			
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


	cout << "details: " << details << endl;
	cout << "date: " << date << endl;
	cout << "time: " << time << endl;
	cout << "priority: " << priority << endl;
	cout << "buffer: " << buffer << endl;
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
		if (pos >= 0) {
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
		if (pos >= 0) {
			return true;
		}
	}
	return false;
}

bool WiseManager::isBuffer(string str) {

	string bufferKey[15] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "at", "on", "-", "from", "to"};
	int pos = -1;

	for (size_t i = 0; i < 15; i++) {
		pos = str.find(bufferKey[i]);
		if (pos >= 0) {
			return true;
		}
	}
	return false;
}