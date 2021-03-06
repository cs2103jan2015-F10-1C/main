#include "ExecuteDirectory.h"


ExecuteDirectory::ExecuteDirectory(UserTask* task) {
	_task = task;
}


ExecuteDirectory::~ExecuteDirectory()
{
}

//@author A0108375A
string ExecuteDirectory::execute(Storage& _storage, ExtDataBase extdb, vector<list<StickyNote>::iterator>& _allItems, bool& successful) {
	string undo = "directory " + extdb.getLocation();
	_undoDirectory.push(undo);

	string newDirectory = _task->getRemaining();
	string result;
	result = extdb.setLocation(_storage, newDirectory, successful);

	return result;
}

string ExecuteDirectory::undo() {

	string undoDirectory;
	undoDirectory = _undoDirectory.top();
	_undoDirectory.pop();

	return undoDirectory;
}