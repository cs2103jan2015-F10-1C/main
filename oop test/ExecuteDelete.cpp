#include "ExecuteDelete.h"


ExecuteDelete::ExecuteDelete(UserTask* task) {
	_task = task;
	_deleted = false;

}


ExecuteDelete::~ExecuteDelete() {
}

string ExecuteDelete::execute(Storage& _storage, ExtDataBase extdb) {

	string indexToBeDeleted = _task->getRemaining();
	indexToBeDeleted = indexToBeDeleted.substr(0, indexToBeDeleted.size() - 2);

	if (indexToBeDeleted.size() != 6){
		return MESSAGE_NOT_DELETED;
	}

	for (size_t i = 0; i < indexToBeDeleted.size(); i++) {
		if (indexToBeDeleted[i] < '0' || indexToBeDeleted[i] > '9') {
			return MESSAGE_NO_INFO_GIVEN;
		}
	}

		//indexToBeDeleted = indexToBeDeleted.substr(0, indexToBeDeleted.size() - 2);
		size_t size = _storage.getSize();
		list<StickyNote>::iterator iter;
		iter = _storage.getIter();

		for (size_t i = 0; i < size; i++, iter++){

			if (indexToBeDeleted == iter->getIndex()){
				string undo;
				undo = _storage.oneTaskInfoTypeTwo(iter);
				undo = "add " + undo;
				_undoDelete.push(undo);
				bool erased = false;
				erased = _storage.erase(iter);
				assert(erased == true);
				_deleted = true;
				break;
			}
		}

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