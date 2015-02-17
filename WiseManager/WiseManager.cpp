#include "WiseManager.h"
#include <vector>
#include <algorithm>
#include <fstream> 

const string ADD_IDENTIFIER = "ADD";
const string DELETE_IDENTIFIER = "DELETE";
const string VIEW_IDENTIFIER = "VIEW";
const string DISPLAY_IDENTIFIER = "DISPLAY";
const string EXIT_IDENTIFIER = "EXIT";

const string TASK_DETAILS_IDENTIFIER = "-info";
const string TASK_DATE_IDENTIFIER = "-date";
const string TASK_TIME_IDENTIFIER = "-time";
const string TASK_PRIORITY_IDENTIFIER = "-prior";

const int POSITION_UNFOUND = -1;

const string ERROR_UNRECOGNISED_COMMAND_TYPE_MESSAGE = "the command type is wrong, please re-enter";
const string NO_ADD_INFO_MESSAGE = "there is no further information given after a command ADD, please re-enter";

WiseManager::WiseManager() {
	_tail = NULL;
	_size=0;
};


WiseManager::~WiseManager(void) {	
};

void WiseManager::initialise(ifstream* detaBaseRead, ofstream* detaBaseWrite) {
	string taskLine;

	while(getline(*detaBaseRead, taskLine)){	
		addTask(taskLine, detaBaseRead, detaBaseWrite);
	}

	return;
};

void WiseManager:: getStarted(ifstream* detaBaseRead, ofstream* detaBaseWrite){
	bool exitFromSystem = false;
	string userInput;
	Command_Type commandType;


	while(!cin.eof() && !exitFromSystem){ 
		cout << "Command:";
		getline(cin, userInput);
		commandType = getCommandType(userInput);
		if(commandType == EXIT){
			exitFromSystem = true;
		}
		else{
			processCommand(commandType, userInput, detaBaseRead, detaBaseWrite);
		}
	}
	return;
}

WiseManager :: Command_Type WiseManager:: getCommandType(string &userInput){
	int startOfCommand = 0, endOfCommand = 0, startOfInfo = 0;
	string command;
	startOfCommand = userInput.find_first_not_of(" ", 0);
	endOfCommand = userInput.find_first_of(" ", startOfCommand);
	command = userInput.substr(startOfCommand, endOfCommand-startOfCommand); 

	if(endOfCommand < 0){
		userInput = "";
	}
	else{
		startOfInfo = userInput.find_first_not_of(" ", endOfCommand+1); 
		userInput = userInput.substr(startOfInfo);
	}
	
	int sizeOfCommand = command.size();
	for(int i=0; i<sizeOfCommand; i++){
		if(islower(command[i])){
			command[i] = toupper(command[i]);
		}
	}

	if(command == ADD_IDENTIFIER){
		return ADD;
	}
	else if (command == DELETE_IDENTIFIER){
		return DELETE;
	}
	else if (command == VIEW_IDENTIFIER){
		return VIEW;
	}
	else if (command == DISPLAY_IDENTIFIER){ 
		return DISPLAY;
	}
	else if (command == EXIT_IDENTIFIER){
		return EXIT;
	}
	else{
		//Generates an error message and requests the user to re-enter the command line.
		printErrorMessage(ERROR_UNRECOGNISED_COMMAND_TYPE_MESSAGE);
		return ERROR;
	}
}

void WiseManager::processCommand(Command_Type commandType, string userInput, ifstream* detaBaseRead, ofstream* detaBaseWrite){
	switch(commandType){
	case ADD:
			if(userInput == ""){
				printErrorMessage(NO_ADD_INFO_MESSAGE);
				return;
			}
			else{
			addTask(userInput, detaBaseRead, detaBaseWrite);
			return;
			}
	case DELETE:
			deleteTask(userInput, detaBaseRead, detaBaseWrite);
			return;
	case EDIT:
			editTask(userInput, detaBaseRead, detaBaseWrite);
			return;
	case VIEW:
			viewTask(userInput);
			return;
	case DISPLAY:
			displayAllTask();
			return;
	case ERROR:
			return;
	}
}

void WiseManager::addTask(string userInput, ifstream* detaBaseRead, ofstream* detaBaseWrite) {
	Task* task = new Task;
	int startOfTaskName = 0, endOfTaskName; // Assume the userInput starts without "add" but the task name.
	int startOfDetail, startOfDate, startOfTime, startOfPriority, endOfDetail, endOfDate, endOfTime, endOfPriority;
	string taskToBeSaved;

	startOfDetail = findPosition(userInput, TASK_DETAILS_IDENTIFIER);
	startOfDate = findPosition(userInput, TASK_DATE_IDENTIFIER);
	startOfTime = findPosition(userInput, TASK_TIME_IDENTIFIER);
	startOfPriority = findPosition(userInput, TASK_PRIORITY_IDENTIFIER);
	
	vector<int> positionToSort;
	positionToSort.push_back(startOfTaskName);

	if(startOfDetail == POSITION_UNFOUND){
		task->taskDetails = "";
	}
	else{
		positionToSort.push_back(startOfDetail);
	}

	if(startOfDate == POSITION_UNFOUND){
		task->date = "";
	}
	else{
		positionToSort.push_back(startOfDate);
	}

	if(startOfTime == POSITION_UNFOUND){
		task->time = "";
	}
	else{
		positionToSort.push_back(startOfTime);
	}

	if(startOfPriority == POSITION_UNFOUND){
		task->priority = "";
	}
	else{
		positionToSort.push_back(startOfPriority);
	}

	if(positionToSort.size()>1){
	sort(positionToSort.begin(), positionToSort.end());
	
	vector<int>::iterator iter1, iter2;
	for(iter1=positionToSort.begin(); iter1!=positionToSort.end()-1; iter1++){
		iter2=iter1 + 1;
		if(*iter1 == startOfTaskName){
			endOfTaskName = *iter2;
		}
		else if(*iter1 == startOfDetail){
			endOfDetail = *iter2;
		}
		else if(*iter1 == startOfDate){
			endOfDate = *iter2;
		}
		else if(*iter1 == startOfTime){
			endOfTime = *iter2;
		}
		else if(*iter1 == startOfPriority){
			endOfPriority = *iter2;
		}
	}

		task->taskName = userInput.substr(startOfTaskName, endOfTaskName-startOfTaskName);
		task->taskName = removeExtraSpace(task->taskName);               
		taskToBeSaved = task->taskName;
		if(startOfDetail != POSITION_UNFOUND){
			task->taskDetails = userInput.substr((startOfDetail+TASK_DETAILS_IDENTIFIER.length()), (endOfDetail-(startOfDetail+TASK_DETAILS_IDENTIFIER.length())));
			task->taskDetails = removeExtraSpace(task->taskDetails);
			taskToBeSaved = taskToBeSaved + " -info " + task->taskDetails;
		}
		if(startOfDate != POSITION_UNFOUND){
			task->date = userInput.substr((startOfDate+TASK_DATE_IDENTIFIER.length()), (endOfDate-(startOfDate+TASK_DATE_IDENTIFIER.length())));
			task->date = removeExtraSpace(task->date);
			taskToBeSaved = taskToBeSaved + " -date " + task->date;
		}
		if(startOfTime != POSITION_UNFOUND){
			task->time = userInput.substr((startOfTime+TASK_TIME_IDENTIFIER.length()), (endOfTime-(startOfTime+TASK_TIME_IDENTIFIER.length())));
			task->time = removeExtraSpace(task->time);
			taskToBeSaved = taskToBeSaved + " -time " + task->time;
		}
		if(startOfPriority != POSITION_UNFOUND){
			task->priority = userInput.substr((startOfPriority+TASK_PRIORITY_IDENTIFIER.length()), (endOfPriority-(startOfPriority+TASK_PRIORITY_IDENTIFIER.length())));
			task->priority = removeExtraSpace(task->priority);
			taskToBeSaved = taskToBeSaved + " -prior " + task->priority;
		}
	}

	else{
	task->taskName = userInput;
	task->taskName = removeExtraSpace(task->taskName);
	taskToBeSaved = task->taskName;
	}

	(*detaBaseWrite) << taskToBeSaved << endl;

	if(_size>0){
		task->next = _tail;
		task->prev = _tail->prev;
		_tail->prev->next = task;
		_tail->prev = task;
		_tail = task;
		_size++;
	}
	else if(_size==0){
		task->next = task;
		task->prev = task;
		_tail = task;
		_size++;
	}

	return;
};

int WiseManager::findPosition(string toBeChecked, const string identifier){
	if(identifier.length()>toBeChecked.length()){
		return POSITION_UNFOUND;
	}
	else{
		size_t startingPointOfStringChecked, startingPointOfIdentifier, positionUnderChecking;
		for(startingPointOfStringChecked=0; startingPointOfStringChecked<toBeChecked.length(); startingPointOfStringChecked++){
			startingPointOfIdentifier=0;
			positionUnderChecking=startingPointOfStringChecked;
			while(positionUnderChecking<toBeChecked.length() && 
									toBeChecked[positionUnderChecking] == identifier[startingPointOfIdentifier]){
				positionUnderChecking++;
				startingPointOfIdentifier++;			
			}
			if(startingPointOfIdentifier==identifier.length()){
				return startingPointOfStringChecked;
			}
		}
		return POSITION_UNFOUND;
	}
}

string WiseManager::removeExtraSpace(string stringTobeModified){
	int start = stringTobeModified.find_first_not_of(" ");
	int end = stringTobeModified.find_last_not_of(" ");
	return stringTobeModified.substr(start, end-start+1);
}

void WiseManager::deleteTask(string userInput, ifstream* detaBaseRead, ofstream* detaBaseWrite) {


};

void WiseManager::editTask(string userInput, ifstream* detaBaseRead, ofstream* detaBaseWrite) {


};

void WiseManager::viewTask(string userInput) {


};

void WiseManager::displayAllTask() {
	Task* currentPosition = _tail->next;  
	for(int i=1; i<=_size; i++){
		cout << i << ". " << currentPosition->taskName << endl;
		currentPosition = currentPosition->next;
	}
	return;
};

void WiseManager::printErrorMessage(string errorMessage){
	cout << errorMessage << endl;
	return;
}