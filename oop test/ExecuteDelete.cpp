#include "ExecuteDelete.h"


ExecuteDelete::ExecuteDelete(UserTask* task) {
	_task = task;
	_deleted = false;

}


ExecuteDelete::~ExecuteDelete() {
}

string ExecuteDelete::execute(Storage& _storage, ExtDataBase extdb, vector<list<StickyNote>::iterator>& _allItems) {

	string indexToBeDeleted = _task->getRemaining();


	for (size_t i = 0; i < indexToBeDeleted.size(); i++) {
		if (indexToBeDeleted[i] < '0' || indexToBeDeleted[i] > '9') {
			return MESSAGE_NO_INFO_GIVEN;
		}
	}

	list<StickyNote>::iterator iter;

	if (indexToBeDeleted.size() == 6) {

		iter = _storage.getIter();
		for (size_t i = 0; i < _storage.getSize(); i++, iter++) {
			if (iter->getIndex() == indexToBeDeleted) {
				break;
			}
		}
	}
	else {
		int forEdit = atoi(indexToBeDeleted.c_str());
		forEdit--;

		if (forEdit < 0 || forEdit > _allItems.size()) {
			return MESSAGE_WRONG_INDEX;
		}

		iter = _allItems[forEdit];
	}


		string undo;
		undo = _storage.oneTaskInfoTypeTwo(iter);
		undo = "add " + undo;
		_undoDelete.push(undo);
		bool erased = false;
		erased = _storage.erase(iter);
		assert(erased == true);
		_deleted = true;


		if (_deleted){
			return MESSAGE_DELETED;
		}
		else{
			return MESSAGE_NOT_DELETED;
		}
}

string ExecuteDelete::undo() {
	string undoDelete;
	undoDelete = _undoDelete.top();
	_undoDelete.pop();
	return undoDelete;
}