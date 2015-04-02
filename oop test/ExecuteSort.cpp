#include "ExecuteSort.h"

ExecuteSort::ExecuteSort(UserTask* task) {
	_task = task;
}


ExecuteSort::~ExecuteSort()
{
}

string ExecuteSort::undo() {
	return "";
}

string ExecuteSort::execute(Storage& _storage, ExtDataBase extdb, vector<list<StickyNote>::iterator>& _allItems) {

	ostringstream oss;
	string desireCommand = _task->getRemaining();

	if (desireCommand == ""){
		return MESSAGE_INVALID_SORT;
	}

	if (desireCommand == "by date"){
		return sortTasksByDate(_storage);
	}
	else if (desireCommand == "by priority"){
		return sortTasksPriority(_storage);
	}
	else{
		return MESSAGE_INVALID_SORT;
	}

	return oss.str();
}

string ExecuteSort::getTodayDate(){
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

string ExecuteSort::getAllInfoOfOneTask(list<StickyNote>::iterator iter){

	ostringstream oss;
	oss << "Index: " << iter->getIndex() << "\r\n"
		<< "Details: " << iter->getDetails() << "\r\n"
		<< "Date: " << iter->getDate() << "\r\n"
		<< "Time: " << iter->getTime() << "\r\n"
		<< "Priority: " << iter->getPriority() << "\r\n";
	return oss.str();

}

string ExecuteSort::sortTasksByDate(Storage& _storage){

	vector<list<StickyNote>::iterator> futureTasks;
	getFutureTasks(futureTasks, _storage);

	ostringstream oss;

	vector<list<StickyNote>::iterator> jan, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec;
	for (size_t i = 0; i < futureTasks.size(); i++){
		switch (futureTasks[i]->getMonth()){
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


	vector<list<StickyNote>::iterator> sortedFutureTasks;
	if (jan.size() > 0){
		std::sort(jan.begin(), jan.end(), compareTwoTasksByDay());
		for (size_t i = 0; i < jan.size(); i++){
			sortedFutureTasks.push_back(jan[i]);
		}
	}
	if (feb.size() > 0){
		std::sort(feb.begin(), feb.end(), compareTwoTasksByDay());
		for (size_t i = 0; i < feb.size(); i++){
			sortedFutureTasks.push_back(feb[i]);
		}
	}
	if (mar.size() > 0){
		std::sort(mar.begin(), mar.end(), compareTwoTasksByDay());
		for (size_t i = 0; i < mar.size(); i++){
			sortedFutureTasks.push_back(mar[i]);
		}
	}
	if (apr.size() > 0){
		std::sort(apr.begin(), apr.end(), compareTwoTasksByDay());
		for (size_t i = 0; i < apr.size(); i++){
			sortedFutureTasks.push_back(apr[i]);
		}
	}
	if (may.size() > 0){
		std::sort(may.begin(), may.end(), compareTwoTasksByDay());
		for (size_t i = 0; i < may.size(); i++){
			sortedFutureTasks.push_back(may[i]);
		}
	}
	if (jun.size() > 0){
		std::sort(jun.begin(), jun.end(), compareTwoTasksByDay());
		for (size_t i = 0; i < jun.size(); i++){
			sortedFutureTasks.push_back(jun[i]);
		}
	}
	if (jul.size() > 0){
		std::sort(jul.begin(), jul.end(), compareTwoTasksByDay());
		for (size_t i = 0; i < jul.size(); i++){
			sortedFutureTasks.push_back(jul[i]);
		}
	}
	if (aug.size() > 0){
		std::sort(aug.begin(), aug.end(), compareTwoTasksByDay());
		for (size_t i = 0; i < aug.size(); i++){
			sortedFutureTasks.push_back(aug[i]);
		}
	}
	if (sep.size() > 0){
		std::sort(sep.begin(), sep.end(), compareTwoTasksByDay());
		for (size_t i = 0; i < sep.size(); i++){
			sortedFutureTasks.push_back(sep[i]);
		}
	}
	if (oct.size() > 0){
		std::sort(oct.begin(), oct.end(), compareTwoTasksByDay());
		for (size_t i = 0; i < oct.size(); i++){
			sortedFutureTasks.push_back(oct[i]);
		}
	}
	if (nov.size() > 0){
		std::sort(nov.begin(), nov.end(), compareTwoTasksByDay());
		for (size_t i = 0; i < nov.size(); i++){
			sortedFutureTasks.push_back(nov[i]);
		}
	}
	if (dec.size() > 0){
		std::sort(dec.begin(), dec.end(), compareTwoTasksByDay());
		for (size_t i = 0; i < dec.size(); i++){
			sortedFutureTasks.push_back(dec[i]);
		}
	}

	for (size_t j = 0; j < sortedFutureTasks.size(); j++){
		oss << j + 1 << "." << getAllInfoOfOneTask(sortedFutureTasks[j]) << "\r\n";
	}

	return oss.str();
}

void ExecuteSort::getFutureTasks(vector<list<StickyNote>::iterator> &futureTasks, Storage& _storage){

	list<StickyNote>::iterator iter = _storage.getIter();
	size_t _size = _storage.getSize();
	time_t rawTime;
	struct tm * timeInfo = new struct tm;

	time(&rawTime);
	localtime_s(timeInfo, &rawTime);

	int dayNow = timeInfo->tm_mday;
	int monthNow = timeInfo->tm_mon + 1;

	for (size_t i = 0; i < _size; i++, iter++){
		string curTaskDate = iter->getDate();
		int posOfSlash = curTaskDate.find_first_of('/', 0);
		string day = curTaskDate.substr(0, posOfSlash);
		string month = curTaskDate.substr(posOfSlash + 1);
		int dayInt = atoi(day.c_str());
		int monthInt = atoi(month.c_str());
		iter->setDay(dayInt);
		iter->setMonth(monthInt);
		if (monthInt>monthNow){
			futureTasks.push_back(iter);
		}
		else if (monthInt == monthNow && dayInt >= dayNow){
			futureTasks.push_back(iter);
		}
		else{
		}
	}

	return;
}

string ExecuteSort::sortTasksPriority(Storage& _storage){
	vector<list<StickyNote>::iterator> futureTasks, highPrior, midPrior, lowPrior, unbounded, sortedTasksByPrior;
	ostringstream oss;

	getFutureTasks(futureTasks, _storage);

	for (size_t i = 0; i <futureTasks.size(); i++){
		if ((futureTasks[i]->getPriority())[0] == 'h'){
			highPrior.push_back(futureTasks[i]);
		}
		else if ((futureTasks[i]->getPriority())[0] == 'm'){
			midPrior.push_back(futureTasks[i]);
		}
		else if ((futureTasks[i]->getPriority())[0] == 'l'){
			lowPrior.push_back(futureTasks[i]);
		}
		else{
			unbounded.push_back(futureTasks[i]);
		}
	}

	if (highPrior.size() > 0){
		for (size_t i = 0; i < highPrior.size(); i++){
			sortedTasksByPrior.push_back(highPrior[i]);
		}
	}
	if (midPrior.size() > 0){
		for (size_t i = 0; i < midPrior.size(); i++){
			sortedTasksByPrior.push_back(midPrior[i]);
		}
	}
	if (lowPrior.size() > 0){
		for (size_t i = 0; i < lowPrior.size(); i++){
			sortedTasksByPrior.push_back(lowPrior[i]);
		}
	}
	if (unbounded.size() > 0){
		for (size_t i = 0; i < unbounded.size(); i++){
			sortedTasksByPrior.push_back(unbounded[i]);
		}
	}

	for (size_t j = 0; j < sortedTasksByPrior.size(); j++){
		oss << j + 1 << "." << getAllInfoOfOneTask(sortedTasksByPrior[j]) << "\r\n";
	}

	return oss.str();
}