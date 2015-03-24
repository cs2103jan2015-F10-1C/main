#pragma once
#include <string>
#include <vector>
#include <fstream>
using namespace std;

class AutomatedTesting
{
private:
	string _automatedTestingFile = "AutomatedTestfile.txt";
	ifstream _testFile;

public:
	AutomatedTesting();
	~AutomatedTesting();

	vector<string> getTestCases();
};