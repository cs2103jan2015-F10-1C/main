#include "Logic.h"


Logic::Logic() {
	_parser = new Parser;
	initialise();
}


Logic::~Logic() {
	delete _parser;
}

string Logic::handleInput(string userInput) {
	
	UserTask* task = _parser->parse(userInput);
	string result;
	Executor* executor;

	if (task->getCommand() == COMMAND::EXIT) {
		exit(0);
	}
	else if (task->getCommand() == COMMAND::ERROR) {
		result = MESSAGE_UNRECOGNISED_COMMAND_TYPE;
	}
	
	else if (task->getCommand() == COMMAND::UNDO) {
		
		if (!_inputHistory.empty()) {
			executor = _inputHistory.top();
			_inputHistory.pop(); 
			string conduct = executor->undo();
			task = _parser->parse(conduct);
			executor = dispatch(task);
			result = executor->execute(_storage, _extdb);
			_extdb.autoSave(_storage);
		}
		else {
			result = MESSAGE_INVALID_UNDO;
		}

	} 
	else {
			 executor = dispatch(task);
			 result = executor->execute(_storage, _extdb);
			 if (task->getCommand() == COMMAND::ADD || task->getCommand() == COMMAND::DELETE
				 || task->getCommand() == COMMAND::EDIT || task->getCommand() == COMMAND::DIRECTORY) {
				 _inputHistory.push(executor);
			 }
			 _extdb.autoSave(_storage);
		 }

	return result;
}

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
	case DISPLAYDROPDOWN:
		return new ExecuteDropDown(task);
	case HELP:
		return new ExecuteHelp(task);
	case MARK:
		return new ExecuteMark(task);
	case DIRECTORY:
		return new ExecuteDirectory(task);
	};
}

void Logic::initialise() {

	vector<string>* vec;

	vec = _extdb.getContent();

	for (int i = 0; i < vec->size(); i++) {
		UserTask* task = _parser->parse((*vec)[i]);
		Executor* execute = dispatch(task);
		execute->execute(_storage, _extdb);
	}
	
}

string Logic::getCurrentDirectory(){
	ifstream in;
	in.open("DirectoryStorage.txt");
	assert(in.is_open() == true);
	string _currentDirectory;
	getline(in, _currentDirectory);

	return _currentDirectory;
}
