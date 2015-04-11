#include "ExecuteDelete.h"


ExecuteDelete::ExecuteDelete(UserTask* task) {
	_task = task;
	_deleted = false;

}

ExecuteDelete::~ExecuteDelete() {
}

//@author A0108341R
string ExecuteDelete::execute(Storage& _storage, ExtDataBase extdb, vector<list<StickyNote>::iterator>& _allItems, bool& successful) {
	string indexToBeDeleted = _task->getRemaining();
	bool isFound = false;

	for (size_t i = 0; i < indexToBeDeleted.size(); i++) {
		try{
			if (indexToBeDeleted[i] < '0' || indexToBeDeleted[i] > '9') {
				successful = false;
				throw MESSAGE_WRONG_INDEX;
			}
		}
		catch (string e){
			return e;
		}
	}

	list<StickyNote>::iterator iter;

	if (indexToBeDeleted.size() == 6) {

		iter = _storage.getIter();
		for (size_t i = 0; i < _storage.getSize(); i++, iter++) {
			if (iter->getIndex() == indexToBeDeleted) {
				isFound = true;
				break;
			}
		}
	}
	else {
		int forEdit = atoi(indexToBeDeleted.c_str());
		forEdit--;

		try{
			if (forEdit < 0 || forEdit >= _allItems.size()) {
				successful = false;
				throw MESSAGE_WRONG_INDEX;
			}
		}
		catch (string e){
			return e;
		}
		isFound = true;
		iter = _allItems[forEdit];
	}

	try{
		if (!isFound) {
			successful = false;
			throw MESSAGE_WRONG_INDEX;
		}
	}
	catch (string e){
		return e;
	}

		string undo;
		undo = _storage.oneTaskInfoTypeTwo(iter);
		undo = "add " + undo;
		_undoDelete.push(undo);
		bool erased = false;
		erased = _storage.erase(iter);
		assert(erased == true);
		_deleted = true;
		_storage.findClashes();

		try{
			if (_deleted){
				successful = true;
				return MESSAGE_DELETED;
			}
			else{
				successful = false;
				throw MESSAGE_NOT_DELETED;
			}
		}
		catch (string e){
			return e;
		}
}

string ExecuteDelete::undo() {
	string undoDelete;
	undoDelete = _undoDelete.top();
	_undoDelete.pop();

	return undoDelete;
}