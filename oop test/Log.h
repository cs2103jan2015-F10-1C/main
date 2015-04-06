#pragma once
#include <string>
#include <fstream>
using namespace std;

class Log {
private:
	string _logFileLocation = "../Log.txt";
	ofstream _writeLog;

public:
	Log();
	~Log();

	void logInfo(string);

};

