#include "ExecuteDisplay.h"
#include <sstream>


ExecuteDisplay::ExecuteDisplay(UserTask* task) {
	_task = task;
}


ExecuteDisplay::~ExecuteDisplay()
{
}

string ExecuteDisplay::execute(Storage& _storage, ExtDataBase extdb, vector<list<StickyNote>::iterator>& _allItems) {

	string displayType = _task->getRemaining();
	ostringstream oss;
	int counter = 1;
	char buffer[100];
	size_t _size = _storage.getSize();
	list<StickyNote>::iterator iter;
	iter = _storage.getIter();
	Date checkDate;
	string result = "";


	if (_size == 0) {
		oss << MESSAGE_NO_TASK_FOUND;
		return oss.str();
	}
	
	else if (displayType == "today" || displayType == "") {
		string currentDate = checkDate.getTodayDate();
		sprintf_s(buffer, MESSAGE_DISPLAY.c_str(), currentDate.c_str());
		oss << buffer << "\r\n";
		for (size_t i = 0; i < _size; i++, iter++) {
			if (iter->getDate() == currentDate) {
				oss << counter << ". " << iter->getDetails()
					<< " [" << iter->getTime() << "]";
				if (iter->getPriority() != "") {
					oss << " [" << iter->getPriority() << "]";
				}
				oss << "\r\n";
				counter++;
			}
		}
		if (counter == 1) { // no task found
			oss << MESSAGE_NO_TASK_FOUND;
		}
	}

	else if (displayType == "high priority" || displayType == "mid priority" || displayType == "low priority") {
		string extract;
		int endOfPrior = displayType.find_first_of(" ", 0);
		extract = displayType.substr(0, endOfPrior);

		sprintf_s(buffer, MESSAGE_DISPLAY.c_str(), displayType.c_str());
		oss << buffer << "\r\n";
		for (size_t i = 0; i < _size; i++, iter++) {
			if (iter->getPriority() == extract) {
				oss << counter << ". " << iter->getDetails()
					<< " [" << iter->getDate() << "]" 
					<< " [" << iter->getTime() << "]" << "\r\n";
				counter++;
			}
		}
		if (counter == 1) { // no task found
			oss << MESSAGE_NO_TASK_FOUND;
		}
	}

	else if (checkDate.isDate1(displayType) || checkDate.isDate2(displayType)) {
		Standardise standard;
		string inputDate = standard.standardiseDate(displayType);
		sprintf_s(buffer, MESSAGE_DISPLAY.c_str(), inputDate.c_str());
		oss << buffer << "\r\n";
		for (size_t i = 0; i < _size; i++, iter++) {
			if (iter->getDate() == inputDate) {
				oss << counter << ". " << iter->getDetails()
					<< " [" << iter->getTime() << "]";
				if (iter->getPriority() != "") {
					oss << " [" << iter->getPriority() << "]";
				}
				oss << "\r\n";
				counter++;
			}
		}
		if (counter == 1) { // no task found
			oss << MESSAGE_NO_TASK_FOUND;
		}
	}
	else if (checkIsMonth(displayType, result, _storage)){
		return result;
	}
	else if (displayType == "all") {
		for (size_t i = 0; i < _size; i++, iter++){
			oss << "[" << iter->getIndex() << "]" << " [" << iter->getCategory() << "]" << "\r\n" 
				<< "Details: " << iter->getDetails() << "\r\n" << "Date: " << iter->getDate() << "\r\n" 
				<< "Time: " << iter->getTime() << "\r\n" << "Priority: " << iter->getPriority() << "\r\n" << "\r\n";
		}
	}
	else{
		return MESSAGE_UNRECOGNISED_DISPLAY_TYPE;
	}
	return oss.str();
}

string ExecuteDisplay::undo() {
	return "";
}

bool ExecuteDisplay::checkIsMonth(string displayType, string &result, Storage& _storage){

	string mthsInYr[24] = { "month jan", "month feb", "month mar", "month apr", "month may", "month jun", "month jul", "month aug", 
		"month sep", "month oct", "month nov", "month dec",
		"month january", "month february", "month march", "month april", "month may", "month june", "month july", "month augest", 
		"month sepetember", "month october", "month november", "month december" };
	int monthInt;
	string monthStr, month;
	size_t _size = _storage.getSize();
	list<StickyNote>::iterator iter;
	iter = _storage.getIter();
	ostringstream oss;
	ostringstream oss2;
	int counter = 1;
	char buffer[100];

	month = displayType.substr(displayType.find_first_of(" ") + 1);
	sprintf_s(buffer, MESSAGE_DISPLAY.c_str(), month.c_str());
	oss << buffer << "\r\n";

	for (int i = 0; i < displayType.size(); i++){
		displayType[i] = tolower(displayType[i]);
	}
	for (int j = 0; j < 24; j++){
		if (mthsInYr[j] == displayType){
			if (j >= 0 && j <= 11){
				monthInt = j + 1;
			}
			else{
				monthInt = j - 11;
			}
			oss2 << monthInt;
			monthStr = oss2.str();

			for (size_t i = 0; i < _size; i++, iter++){
				string date = iter->getDate();
				string month = date.substr(date.find_first_of('/') + 1);
				if (month == monthStr){
					oss << "[" << iter->getIndex() << "]" << " [" << iter->getCategory() << "]" << "\r\n"
						<< "Details: " << iter->getDetails() << "\r\n" << "Date: " << iter->getDate() << "\r\n"
						<< "Time: " << iter->getTime() << "\r\n" << "Priority: " << iter->getPriority() << "\r\n" << "\r\n";
					counter++;
				}
			}
			result = oss.str();
			return true;
		}
	}
	return false;
}