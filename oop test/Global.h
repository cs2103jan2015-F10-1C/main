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
#include <queue>


using namespace std;

const string MESSAGE_WELCOME = "Welcome to Wise Manager V0.5! \n";
const string MESSAGE_OUTDATED = "The following tasks are expired. Please use \"search\" to find the tasks, and use delete/edit/mark commands to modify them. \r\n";
const string MESSAGE_ADD = "New task has been added successfully.\n";
const string MESSAGE_ERROR = "Invalid input. \n";
const string MESSAGE_INFO_UNFOUND = "This keyword is not found. \n";
const string MESSAGE_NO_INFO_GIVEN = "There is no keyword inputed to be searched. \n";
const string MESSAGE_UNRECOGNISED_COMMAND_TYPE = "Command not recognised. Please re-input. \n";
const string MESSAGE_DISPLAY = "Displaying %s task(s)\n";
const string MESSAGE_UNRECOGNISED_DISPLAY_TYPE = "Display type not recognised. Please re-input. \n";
const string MESSAGE_DELETED = "The Task have been deleted successfully. \n";
const string MESSAGE_NOT_DELETED = "The Task have not been deleted. Please Check your inputs. \n";
const string MESSAGE_EDIT = "The Task have been edited successfully. \n";
const string MESSAGE_WRONG_INDEX = "This index is not found. \n";
const string MESSAGE_INVALID_DATE = "This is an invalid date. \n";
const string MESSAGE_INVALID_TIME = "This is an invalid time/deadline. \n";
const string MESSAGE_NO_TASK_FOUND = "No task found. \n";
const string MESSAGE_DIRECTORY_CHANGED = "The saving file directory has been changed. \n";
const string MESSAGE_DIRECTORY_NOT_CHANGED = "The new directory is not found. Please re-input. \n";
const string MESSAGE_INVALID_HELP = "Help is available for the following functions: \nadd, display, delete, edit, search, directory, sort and mark. \nPlease key in, for example: \"help add\" to learn more about the add function.\n";
const string MESSAGE_INVALID_UNDO = "There is nothing to undo. \n";
const string MESSAGE_INVALID_SORT = "The sort criteria is invalid. \n";
const string MESSAGE_MARKED = "task has been marked as cleared\n";
const string MESSAGE_SUCCESSFUL_SEARCH = "The following tasks are found with the specified key words: ";
const string MESSAGE_SUCCESSFUL_SORTED = "The tasks are sorted successfully.";
const string MESSAGE_HOME_RETURN = "Please enter \"display\" or enter any valid operations to return to home screen. \r\n";
const string MESSAGE_EMPTY_SEARCH = "There are no tasks found containing the search term. \r\n";
const string MESSAGE_NO_DATE_GIVEN = "There is no date given. \r\n";
const string SUCCESSFUL_LOG = "Continue...";
const string DEFAULT_SAVE_LOCATION = "D:/Storage.txt";
const string MESSAGE_NO_TODAY_DATE = "Unable to get today's date. \r\n";
const string MESSAGE_NO_TMR_DATE = "Unable to get tomorrow's date. \r\n";
const string MESSAGE_NO_X_DAY_LATER = "Unable to get the date. \r\n";
const int SEC_PER_DAY = 24 * 60 * 60;
const int DAY_PER_SOLAR_MONTH_OF_31 = 31;
const int DAY_PER_SOLAR_MONTH_OF_30 = 30;
const int DAY_OF_FEB_IN_LEAP_YEAR = 29;
const int DAY_OF_FEB_IN_NON_LEAP_YEAR = 28;
const int MONTH_PER_YEAR = 12;
const int SYSTEM_TIME_YEAR_STARTING_POINT = 1900;
const int DAY_PER_WEEK = 7;

enum COMMAND {

	ADD,DELETE,EDIT,SEARCH,DISPLAY,DIRECTORY,HELP,ERROR,EXIT,UNDO, MARK

};
