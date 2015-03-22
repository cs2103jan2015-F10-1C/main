#include "UserTask.h"


UserTask::UserTask()
{
}


UserTask::~UserTask()
{
}

void UserTask::setCommand(COMMAND cmd) {
	_command = cmd;

}

COMMAND UserTask::getCommand() {
	return _command;

}

void UserTask::setRemaining(string remains) {
	_remaining = remains;

}

string UserTask::getRemaining() {
	return _remaining;

}

