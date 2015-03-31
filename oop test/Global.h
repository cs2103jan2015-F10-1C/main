#pragma once

#include <iostream>
#include <string>
#include <list>
#include <assert.h>
#include <fstream>
#include <sstream>
#include <stack>
#include <ctime>
#include <algorithm>
#include <vector>
#include <stdio.h>

using namespace std;

const string MESSAGE_WELCOME = "Welcome to Wise Manager V0.3! \r\n";
const string MESSAGE_ADD = "The following new task has been added successfully.\r\n";
const string MESSAGE_ERROR = "Invalid input. \r\n";
const string MESSAGE_EDIT = "The Task have been edited successfully to \r\n";
const string MESSAGE_INFO_UNFOUND = "This keyword is not found. \r\n";
const string MESSAGE_NO_INFO_GIVEN = "There is no keyword inputed to be searched. \r\n";
const string MESSAGE_UNRECOGNISED_COMMAND_TYPE = "Command not recognised. Please re-input. \r\n";
const string MESSAGE_DISPLAY = "Displaying %s task(s)\r\n";
const string MESSAGE_UNRECOGNISED_DISPLAY_TYPE = "Display type not recognised. Please re-input. \r\n";
const string MESSAGE_DELETED = "The following task have been deleted successfully. \r\n";
const string MESSAGE_NOT_DELETED = "The Task have not been deleted. Please Check your inputs. \r\n";
const string MESSAGE_WRONG_INDEX = "This index is not found. \r\n";
const string MESSAGE_NO_TASK_FOUND = "No task found. \r\n";
const string MESSAGE_DIRECTORY_CHANGED = "The saving file directory has been changed to the following location. \r\n";
const string MESSAGE_DIRECTORY_NOT_CHANGED = "The new directory is not found. Please re-input. \r\n";
const string MESSAGE_INVALID_HELP = "Help is available for the following functions: \nadd, display, delete, edit, search, directory, sort and mark. \nPlease key in, for example: \"help add\" to learn more about the add function.\r\n";
const string MESSAGE_INVALID_UNDO = "There is nothing to undo. \r\n";
const string MESSAGE_INVALID_SORT = "The sort criteria is invalid. \r\n";
const string MESSAGE_MARKED = "Task has been marked as cleared. \r\n";


const string DEFAULT_SAVE_LOCATION = "D:/Storage.txt";

enum COMMAND {

	ADD,DELETE,EDIT,SEARCH,DISPLAY,SORT,DISPLAYDROPDOWN,DIRECTORY,HELP,ERROR,EXIT,UNDO, MARK

};
