#include "ExecuteDirectory.h"


ExecuteDirectory::ExecuteDirectory(UserTask* task) {
	_task = task;
}


ExecuteDirectory::~ExecuteDirectory()
{
}

string ExecuteDirectory::execute(Storage& _storage, ExtDataBase extdb) {

	string undo = extdb.getLocation();
	_undoDirectory.push(undo);

	string newDirectory = _task->getRemaining();
	string result;

	result = extdb.setLocation(_storage, newDirectory);

	return result;
}

string ExecuteDirectory::undo() {

	string undoDirectory;
	undoDirectory = _undoDirectory.top();
	_undoDirectory.pop();
	return undoDirectory;
}