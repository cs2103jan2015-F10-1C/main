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
#include <fstream>

using namespace std;


class WiseManager
{
private:

	// Tentatively, each entry is stored as a Node in a linked list. 
	// subject to changes in future as more functions are implemented.

	struct Task {

		string taskName;
		string taskDetails;
		string date;
		string time;
		string priority;

		Task* prev;
		Task* next;

	};

	enum Command_Type{
		ADD, VIEW, DELETE, EDIT, DISPLAY, EXIT, ERROR
	};

	// include any global variables required here

	// include members here

	Command_Type getCommandType(string&);
	void processCommand(Command_Type, string, ifstream*, ofstream*);
	void addTask(string, ifstream*, ofstream*);
	void deleteTask(string, ifstream*, ofstream*);
	void editTask(string, ifstream*, ofstream*);
	void viewTask(string);
	void displayAllTask();
	int findPosition(string, const string);
	string removeExtraSpace(string);
	void printErrorMessage(string);
	Task* _tail;
	int _size;

public:
	WiseManager();
	~WiseManager();
	
	// include initialiser here
	void initialise(ifstream*, ofstream*);
	void getStarted(ifstream*, ofstream*);
};

