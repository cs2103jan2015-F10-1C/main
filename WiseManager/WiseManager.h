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
#include "stdlib.h"
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
		int day = 0;
		int month = 0;
		bool done = false;

		Task* prev = NULL;
		Task* next = NULL;

	};

	struct compareTwoTasksByDay{
		inline bool operator()(const Task* lhs, const Task* rhs) {
			return lhs->day < rhs->day;
		}
	};

	enum Command_Type{
		ADD, VIEW, DELETE, EDIT, DISPLAY, SEARCH, EXIT, ERROR
	};

	// include any global variables required here

	int _size;
	Task* _tail;

public:
	// include members here
	void autoSave(ofstream*, string);
	void transferDataToList(string);
	int findPosition(string, string);
	string removeSpace(string);
	void executeCommand(string, ofstream*, int*, string*, string);
	Command_Type identifyCommand(string);
	void printMessage(string);
	string addTask(string);
	void splitString(string);
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
	string getAllInfoOfOneTask2(Task*);
	bool haveThisInfo(string, Task*);
	bool compareStrings(string, string);
	void transferData(ofstream*, ifstream*);
	string getTodayTask();
	string getTodayDate();
	string sortTasksByDate();


	WiseManager();
	~WiseManager();

	// include initialiser here
	void initialise(ifstream*, ofstream*, string);
	void getStarted(ifstream*, ofstream*, string);
};

