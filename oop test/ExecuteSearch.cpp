#include "ExecuteSearch.h"


ExecuteSearch::ExecuteSearch(UserTask* task) {
	_task = task;
}


ExecuteSearch::~ExecuteSearch()
{
}

string ExecuteSearch::execute(Storage& _storage, ExtDataBase extdb, vector<list<StickyNote>::iterator>& _allItems) {

	_allItems.clear();

	string infoToBeSearched = _task->getRemaining();
	list<StickyNote>::iterator iter;
	iter = _storage.getIter();
	int _size = _storage.getSize();

	if (infoToBeSearched == ""){
		return MESSAGE_NO_INFO_GIVEN;
	}

	bool infoIsFound = false;
	int i = 0;
	for (iter; i < _size; i++, iter++){
		if (haveThisInfo(infoToBeSearched, iter)){
			infoIsFound = true;
			_allItems.push_back(iter);
		}
	}

	if (infoIsFound){
		string returnMsg;
		returnMsg = MESSAGE_SUCCESSFUL_SEARCH + infoToBeSearched + "\r\n" + MESSAGE_HOME_RETURN;
		return returnMsg;
	}
	else{
		return MESSAGE_INFO_UNFOUND;
	}
}

bool ExecuteSearch::haveThisInfo(string infoToBeSearched, list<StickyNote>::iterator iter) {

	string details, date, time, priority;
	if (iter->getDetails() == ""){
		details = "";
	}
	else{
		details = iter->getDetails();
	}

	if (iter->getDate() == "unbounded event"){
		date = "";
	}
	else{
		date = iter->getDate();
	}

	if (iter->getTime() == "All day event"){
		time = "";
	}
	else{
		time = iter->getTime();
	}

	if (iter->getPriority() == ""){
		priority = "";
	}
	else{
		priority = iter->getPriority();
	}
	
	return (compareStrings(infoToBeSearched, details) || compareStrings(infoToBeSearched, date) ||
		compareStrings(infoToBeSearched, time) || compareStrings(infoToBeSearched, priority));
}

bool ExecuteSearch::compareStrings(string infoToBeSearched, string infoToBeChecked) {

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

			if (startingPosOfInfo == infoToBeSearched.length()){
				return true;
			}
		}
		return false;
	}
}

string ExecuteSearch::undo() {
	return "";
}