#include "ExecuteMark.h"


ExecuteMark::ExecuteMark(UserTask* task) {
	_task = task;
}


ExecuteMark::~ExecuteMark()
{
}

string ExecuteMark::execute(Storage& _storage, ExtDataBase _extdb, vector<list<StickyNote>::iterator>& _allItems, bool& successful) {

	string index = _task->getRemaining();

	if (index.size() != 6) {
		return MESSAGE_ERROR;
	}

	for (int i = 0; i < index.size(); i++) {
		if (index[i] < '0' || index[i] > '9') {
			return MESSAGE_WRONG_INDEX;
		}
	}

	list<StickyNote>::iterator iter;
	iter = _storage.getIter();
	int size = _storage.getSize();
	bool isFound = false;
	vector<list<StickyNote>::iterator> vec;
	string old;

	for (int i = 0; i < size; i++, iter++) {
		if (iter->getIndex() == index) {
			iter->setStatus("cleared");
			isFound = true;
			vec.push_back(iter);
			old = _storage.oneTaskInfoTypeOne(iter);
			_extdb.archive(old);
		}
	}

	while (!vec.empty()) {
		_storage.erase(vec.back());
		vec.pop_back();
	}

	if (isFound) {
		successful = true;
		return MESSAGE_MARKED;
	}
	else {
		return MESSAGE_WRONG_INDEX;
	}
}

string ExecuteMark::undo() {
	return "";
}