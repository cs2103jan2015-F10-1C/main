#include "UserTask.h"


UserTask::UserTask()
{
}

UserTask::~UserTask()
{
}
//@author A0110748J
void UserTask::setCommand(COMMAND cmd) {
	_command = cmd;

}
//@author A0093863U
COMMAND UserTask::getCommand() {
	return _command;

}
//@author A0108341R
void UserTask::setRemaining(string remains) {
	_remaining = remains;

}
//@author A0108375A
string UserTask::getRemaining() {
	return _remaining;

}

