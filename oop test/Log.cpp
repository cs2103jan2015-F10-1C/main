#include "Log.h"


Log::Log() {
	_writeLog.open(_logFileLocation);
}


Log::~Log() {
	_writeLog.close();
}
 
void Log::logInfo(string info){
	_writeLog << info;
	return;
}