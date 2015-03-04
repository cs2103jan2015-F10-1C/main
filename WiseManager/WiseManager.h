#pragma once

//Wise Manager V0.1. 
// Only basic (CRUD) functions will be included in this revision.
// ADD (create): user able to add tasks to database.
// DELETE: user able to delete task from database.
// VIEW (read): user able to view specific task.
// EDIT (update): user able to modify existing entries in database.
// SEARCH (additional function required): used by delete, view and edit functions to source for specified task.

//WiseManager has been applied as static library. no executables will be generated on compilation. 

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <ctime>

using namespace std;


class WiseManager
{
private:

	// Tentatively, each entry is stored as a Node in a linked list. 
	// subject to changes in future as more functions are implemented.

	struct Task {

		string details = "";
		string date = "";
		string time = "";
		string priority = "";

		Task* prev = NULL;
		Task* next = NULL;

	};

	enum Command_Type{
		ADD, VIEW, DELETE, EDIT, DISPLAY, SEARCH, EXIT, ERROR
	};

	// include any global variables required here

	int _size;
	Task* _tail;

public:
	// include members here
	void executeCommand(string, ifstream*, ofstream*, int*, string*);
	Command_Type identifyCommand(string);
	void printMessage(string);
	string addTask(string, ifstream*, ofstream*);
	void splitString(string, ifstream*, ofstream*);
	bool isSpecialDetail(string);
	bool isPriority(string);
	bool isTime(string);
	bool isDate1(string);
	bool isDate2(string);
	bool isBuffer(string);
	string standardiseDate(string);
	string standardiseTime(string);
	string displayTask(string);
	string displayAllTask();
	string searchTask(string);
	string deleteTask(string);
	string editTask(string);
	string showMatchingTasks(vector<Task*>*, string);
	bool isSameTask(Task*, Task*);
	void identifyChange(string*, string*);
	string getAllInfoOfOneTask(Task*);
	bool haveThisInfo(string, Task*);
	bool compareStrings(string, string);
	void transferData(ofstream*, ifstream*);


	WiseManager();
	~WiseManager();

	// include initialiser here
	void initialise(ifstream*, ofstream*);
	void getStarted(ifstream*, ofstream*);
};

