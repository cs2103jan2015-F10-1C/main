#include "WiseManager.h"


int main(void) {

	WiseManager toDo;

	string dataBaseFileName, determinator;

	cout << "Do you have an existing database? [Y/N] ";
	getline(cin, determinator);
	ifstream* detaBaseRead = new ifstream;
	ofstream* detaBaseWrite = new ofstream; 

	while(determinator!="Y" && determinator!="N"){
		cout << "Incorrect choice! Re-enter: ";
		getline(cin, determinator);
	}

	if(determinator == "Y"){
		cout << "Please enter your database filename: ";
		getline(cin, dataBaseFileName);
		toDo.setFileDirectory(dataBaseFileName, "fileNameStorage.txt");
		detaBaseRead->open(dataBaseFileName);
		detaBaseWrite->open("temp.txt"); 
		toDo.initialise(detaBaseRead, detaBaseWrite, "temp.txt");
		toDo.getStarted(detaBaseRead, detaBaseWrite, "temp.txt", "fileNameStorage.txt");
		detaBaseRead->close();
		detaBaseWrite->close();

		detaBaseRead->open("temp.txt");
		detaBaseWrite->open(dataBaseFileName);
		toDo.transferData(detaBaseWrite, detaBaseRead);
		detaBaseRead->close();
		detaBaseWrite->close();
	}
	else if(determinator == "N"){
		cout << "Please enter a database filename for creation: ";
		getline(cin, dataBaseFileName);
		toDo.setFileDirectory(dataBaseFileName, "fileNameStorage.txt");
		detaBaseWrite->open(dataBaseFileName);
		toDo.getStarted(detaBaseRead, detaBaseWrite, dataBaseFileName, "fileNameStorage.txt");
		detaBaseWrite->close();
	}

	return 0;
};
