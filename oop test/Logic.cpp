#include "Logic.h"


Logic::Logic() {
	_parser = new Parser;
	
	initialise();
}


Logic::~Logic() {
	delete _parser;
}
//@author A0110748J
string Logic::handleInput(string userInput, bool& edited, bool& successful) {
	
	UserTask* task = _parser->parse(userInput);
	string result;
	Executor* executor;

	if (task->getCommand() == COMMAND::EXIT) {
		archive();
		_extdb.autoSave(_storage);
		exit(0);
	}
	else if (task->getCommand() == COMMAND::ERROR) {
		successful = false;
		result = MESSAGE_UNRECOGNISED_COMMAND_TYPE;
	}
	
	else if (task->getCommand() == COMMAND::UNDO) {
		
		if (!_inputHistory.empty()) {
			executor = _inputHistory.top();
			_inputHistory.pop(); 
			string conduct = executor->undo();
			task = _parser->parse(conduct);
			executor = dispatch(task);
			result = executor->execute(_storage, _extdb, _allItems, successful);
			_extdb.autoSave(_storage);
		}
		else {
			successful = false;
			result = MESSAGE_INVALID_UNDO;
		}

	} 
	else {
			 executor = dispatch(task);
			 if (task->getCommand() == COMMAND::ADD || task->getCommand() == COMMAND::DELETE
				 || task->getCommand() == COMMAND::EDIT || task->getCommand() == COMMAND::DIRECTORY ||
				 task->getCommand() == COMMAND::MARK) {
				 _inputHistory.push(executor);
			 }
			 result = executor->execute(_storage, _extdb, _allItems, successful);
			 _extdb.autoSave(_storage);
		 }

	if (task->getCommand() == COMMAND::ADD || task->getCommand() == COMMAND::DELETE
		|| task->getCommand() == COMMAND::EDIT || task->getCommand() == COMMAND::UNDO
		|| task->getCommand() == COMMAND::MARK || task->getCommand() == COMMAND::SEARCH) {
		edited = true;
	}
	

	return result;
}
//@author A0093863U
Executor* Logic::dispatch(UserTask* task) {

	switch (task->getCommand()) {
	case ADD:
		return new ExecuteAdd(task);
	case DELETE:
		return new ExecuteDelete(task);
	case EDIT:
		return new ExecuteEdit(task);
	case SEARCH:
		return new ExecuteSearch(task);
	case DISPLAY:
		return new ExecuteDisplay(task);
	case HELP:
		return new ExecuteHelp(task);
	case MARK:
		return new ExecuteMark(task);
	case DIRECTORY:
		return new ExecuteDirectory(task);
	};
}
//@author A0108375A
void Logic::initialise() {

	vector<string>* vec;

	vec = _extdb.getContent();
	bool successful = false;

	for (int i = 0; i < vec->size(); i++) {
		UserTask* task = _parser->parse((*vec)[i]);
		Executor* execute = dispatch(task);
		execute->execute(_storage, _extdb, _allItems, successful);
	}
	
}
//@author A0108341R
string Logic::getCurrentDirectory(){
	
	return _extdb.getLocation();
}

void Logic::archive() {

	vector<list<StickyNote>::iterator> vec;

	list<StickyNote>::iterator iter;
	iter = _storage.getIter();
	int _size = _storage.getSize();
	string old;

	for (int i = 0; i < _size; i++, iter++) {
		old.clear();
		if (iter->getStatus() == "cleared") {
			old = _storage.oneTaskInfoTypeOne(iter);
			_extdb.archive(old);
			vec.push_back(iter);
		}
	}

	while (!vec.empty()) {
		_storage.erase(vec.back());
		vec.pop_back();
	}

}
