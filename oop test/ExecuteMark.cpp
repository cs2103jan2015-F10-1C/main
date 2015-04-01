#include "ExecuteMark.h"


ExecuteMark::ExecuteMark(UserTask* task) {
	_task = task;
}


ExecuteMark::~ExecuteMark()
{
}

string ExecuteMark::execute(Storage& _storage, ExtDataBase _extdb, vector<list<StickyNote>::iterator>& _allItems, bool& successful) {

	string index = _task->getRemaining();
	string old;
	bool isFound = false;
	bool isUndo = false;
	string type = index.substr(0, 4);
	if (type == "undo") {
		isUndo = true;
		index = index.substr(5);
	}

	for (size_t i = 0; i < index.size(); i++) {
		if (index[i] < '0' || index[i] > '9') {
			return MESSAGE_WRONG_INDEX;
		}
	}

	list<StickyNote>::iterator iter;

	if (index.size() == 6) {

		iter = _storage.getIter();
		for (size_t i = 0; i < _storage.getSize(); i++, iter++) {
			if (iter->getIndex() == index) {
				isFound = true;
				old = _storage.oneTaskInfoTypeOne(iter);
				break;
			}
		}
	}
	else {
		int forEdit = atoi(index.c_str());
		forEdit--;

		if (forEdit < 0 || forEdit >= _allItems.size()) {
			return MESSAGE_WRONG_INDEX;
		}

		isFound = true;
		iter = _allItems[forEdit];
		old = _storage.oneTaskInfoTypeOne(iter);
	}

	if (isUndo) {
		iter->setStatus("incomplete");
		_storage.findClashes();
		return MESSAGE_MARKED;

	}

	if (isFound && !isUndo) {
		successful = true;
		string undo = "mark undo " + iter->getIndex();
		_undoMark.push(undo);
		iter->setStatus("cleared");
		_storage.findClashes();
		return MESSAGE_MARKED + old;
	}
	else {
		return MESSAGE_WRONG_INDEX;
	}
}

string ExecuteMark::undo() {

	string undoMark;
	undoMark = _undoMark.top();
	_undoMark.pop();
	return undoMark;
}