#include "Log.h"


Log::Log() {
	_writeLog.open(_logFileLocation);
}

Log::~Log() {
	_writeLog.close();
}

//@author A0108375A
void Log::logInfo(string info){
	_writeLog << info;
	return;
}