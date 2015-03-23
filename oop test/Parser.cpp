#include "Parser.h"


Parser::Parser() {
	_task = new UserTask; 
}


Parser::~Parser(){
	delete _task;
}

UserTask* Parser::parse(string command) {


	string temp = "", remainingCommand = "";
	int startOfCommand = command.find_first_not_of(" ", 0);
	int endOfCommand = command.find_first_of(" ", startOfCommand);
	if (endOfCommand < 0){
		command = command.substr(startOfCommand);
		remainingCommand = "";
	}
	else{
		temp = command.substr(startOfCommand, endOfCommand - startOfCommand);
		int startOfRemaining = command.find_first_not_of(" ", endOfCommand);
		if (startOfRemaining < 0){
			remainingCommand = "";
		}
		remainingCommand = command.substr(startOfRemaining);
		command = temp;
	}

	if (command[command.length() - 2] == '\r'&&command[command.length() - 1] == '\n'){
		size_t commandSize = command.length() - 2;  // Ignore the "/r/n" of the string.
		for (size_t index = 0; index < commandSize; index++) {
			command[index] = tolower(command[index]);
		}
		command = command.substr(0, commandSize);  // Remove "/r/n" of the string from UI.
	}

	else{
		for (size_t index = 0; index < command.length(); index++) {
			command[index] = tolower(command[index]);
		}
	}

	_task->setRemaining(remainingCommand);

	if (command == "add") {
		_task->setCommand( COMMAND::ADD );
	}
	else if (command == "delete") {
		_task->setCommand(COMMAND::DELETE);
	}
	else if (command == "edit") {
		_task->setCommand(COMMAND::EDIT);
	}
	else if (command == "display") {
		_task->setCommand(COMMAND::DISPLAY);
	}
	else if (command == "search") {
		_task->setCommand(COMMAND::SEARCH);
	}
	else if (command == "exit") {
		_task->setCommand(COMMAND::EXIT);
	}
	else if (command == "directory") {
		_task->setCommand(COMMAND::DIRECTORY);
	}
	else if (command == "help") {
		_task->setCommand(COMMAND::HELP);
	}
	else if (command == "undo") {
		_task->setCommand(COMMAND::UNDO);
	}
	else if (command == "mark") {
		_task->setCommand(COMMAND::MARK);
	}
	else
		_task->setCommand(COMMAND::ERROR);

	return _task;

}