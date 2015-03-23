#include "ExecuteDisplay.h"


ExecuteDisplay::ExecuteDisplay(UserTask* task) {
	_task = task;
}


ExecuteDisplay::~ExecuteDisplay()
{
}

string ExecuteDisplay::execute(Storage& _storage, ExtDataBase extdb) {

	string displayType = _task->getRemaining();
	displayType = displayType.substr(0, displayType.size() - 2);
	ostringstream oss;
	int counter = 1;
	char buffer[100];
	size_t _size = _storage.getSize();
	list<StickyNote>::iterator iter;
	iter = _storage.getIter();
	Date checkDate;

	//displayType = displayType.substr(0, displayType.size() - 2);

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
		oss << buffer;
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
		oss << buffer;
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