#include "ExecuteMark.h"


ExecuteMark::ExecuteMark(UserTask* task) {
	_task = task;
}


ExecuteMark::~ExecuteMark()
{
}
//@author A0093863U
string ExecuteMark::execute(Storage& _storage, ExtDataBase _extdb, vector<list<StickyNote>::iterator>& _allItems, bool& successful) {

	string index = _task->getRemaining();
	bool isFound = false;
	bool isUndo = false;
	string type = index.substr(0, 4);
	if (type == "undo") {
		isUndo = true;
		index = index.substr(5);
	}

	for (size_t i = 0; i < index.size(); i++) {
		if (index[i] < '0' || index[i] > '9') {
			successful = false;
			return MESSAGE_WRONG_INDEX;
		}
	}

	list<StickyNote>::iterator iter;

	if (index.size() == 6) {

		iter = _storage.getIter();
		for (size_t i = 0; i < _storage.getSize(); i++, iter++) {
			if (iter->getIndex() == index) {
				isFound = true;
				break;
			}
		}
	}
	else {
		int forEdit = atoi(index.c_str());
		forEdit--;

		if (forEdit < 0 || forEdit >= _allItems.size()) {
			successful = false;
			return MESSAGE_WRONG_INDEX;
		}

		isFound = true;
		iter = _allItems[forEdit];
	}

	if (isUndo) {
		iter->setStatus("incomplete");
		_storage.findClashes();
		successful = true;
		return MESSAGE_MARKED;

	}

	if (isFound && !isUndo) {
		string undo = "mark undo " + iter->getIndex();
		_undoMark.push(undo);
		iter->setStatus("cleared");
		_storage.findClashes();
		successful = true;
		return MESSAGE_MARKED;
	}
	else {
		successful = false;
		return MESSAGE_WRONG_INDEX;
	}
}

string ExecuteMark::undo() {

	string undoMark;
	undoMark = _undoMark.top();
	_undoMark.pop();
	return undoMark;
}