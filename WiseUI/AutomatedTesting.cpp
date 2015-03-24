#include"AutomatedTesting.h"

AutomatedTesting::AutomatedTesting()
{
	_testFile.open(_automatedTestingFile);
}


AutomatedTesting::~AutomatedTesting()
{
}

vector<string> AutomatedTesting::getTestCases(){
	vector<string> testCasesVec;
	string aCase = "";
	while (!_testFile.eof()){
		getline(_testFile, aCase);
		testCasesVec.push_back(aCase);
	}
	return testCasesVec;
}