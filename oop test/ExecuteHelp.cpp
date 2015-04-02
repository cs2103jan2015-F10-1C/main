#include "ExecuteHelp.h"


ExecuteHelp::ExecuteHelp(UserTask* task) {
	_task = task;
}


ExecuteHelp::~ExecuteHelp()
{
}


string ExecuteHelp::execute(Storage& _storage, ExtDataBase extdb, vector<list<StickyNote>::iterator>& _allItems) {

	ostringstream oss;
	string desireCommand = _task->getRemaining(); 

	if (desireCommand == ""){
		return MESSAGE_INVALID_HELP;
	}

	if (desireCommand == "add"){

		oss << "To use ADD, it should be input in the following format: " << "\r\n"
			<< "\r\n"
			<< "1. add <details of the task> date time -priority				or" << "\r\n"
			<< "2. add <details of the task> time date -priority				or" << "\r\n" << "\r\n"
			<< "An example of a simple add task input will be: " << "\r\n"
			<< "1.	add do homework 3 march 5pm -high" << "\r\n"
			<< "this means adding the task do homework on 3 march at 5pm with high priority" << "\r\n"
			<< "\r\n"
			<< "1.1	Possible flexicommands variations for adding a task will be: " << "\r\n"
			<< "\r\n"
			<< "For the inclusion of time, indicate with :, am or pm." << "\r\n"
			<< "there should be no space between time and am / pm (e.g.have dinner 5pm) " << "\r\n"
			<< "The following inputs are wrong : have dinner 5 pm OR have dinner 5 : 00" << "\r\n"
			<< "\r\n"

			<< "1.2	For the inclusion of date, do note that the inputs are in (dd/mm)" << "\r\n"
			<< "\r\n"
			<< "1. 3 mar" << "\r\n"
			<< "2. 3 march" << "\r\n"
			<< "3. mar 3" << "\r\n"
			<< "4. today" << "\r\n"
			<< "5. tomorrow" << "\r\n"
			<< "6. days of week(monday - sunday)" << "\r\n"
			<< "\r\n"

			<< "1.3	For the priority of the task, it can be varied according with inputs: " << "\r\n"
			<< "\r\n"
			<< "1. -high represents task of high priority." << "\r\n"
			<< "2. -mid represents task of medium priority." << "\r\n"
			<< "3. -low represents task of low priority." << "\r\n"
			<< "\r\n"

			<< "1.4	For details with conflicting terms such as certain days in a week and am / pm, user needs to include a quotation mark" << "\r\n"
			<< "\r\n"
			<< "To avoid creating a task on tuesday or at 3pm." << "\r\n"
			<< "e.g.meet at \"taco tuesday\" or meet at \"cafe 3pm\" or \"high tea\"" << "\r\n"
			<< "\r\n";
	}
	else if (desireCommand == "display"){

		oss << "To use DISPLAY, it should be input in the following format: " << "\r\n"
			<< "1. display" << "\r\n"
			<< "2. display today" << "\r\n"
			<< "to display task that are scheduled only for today" << "\r\n"
			<< "3. display tomorrow" << "\r\n"
			<< "to display task that are scheduled only for tomorrow" << "\r\n"
			<< "4. display 3 march" << "\r\n"
			<< "5. display 3/3" << "\r\n"
			<< "to display task that are scheduled only on a specific date" << "\r\n"
			<< "6. display high priority" << "\r\n"
			<< "to display task that are scheduled based on priority" << "\r\n"
			<< "7. display [day]" << "\r\n"
			<< "to display task of the particular day" << "\r\n"
			<< "8. display month mar" << "\r\n"
			<< "to display task of march" << "\r\n"
			<< "9. display month march" << "\r\n"
			<< "to display task of march"
			<< "\r\n"
			<< "\r\n";
	}
	else if (desireCommand == "search"){

		oss << "To use SEARCH, it should be input in the following format: " << "\r\n"
			<< "search <task description>" << "\r\n"
			<< "the function will then return the tasks with the keywords input by the user. " << "\r\n"
			<< "please take note the the task indexes (6 number) as they will be used for delete and edit purposes" << "\r\n"
			<< "\r\n";
	}
	else if (desireCommand == "delete"){

		oss << "To use DELETE, it should be input in the following format: " << "\r\n"
			<< "delete <task index>" << "\r\n"
			<< "1. delete 000001" << "\r\n"
			<< "the function will then delete the task with the 000001 index in the task list. " << "\r\n"
			<< "\r\n";
	}
	else if (desireCommand == "edit"){

		oss << "To use EDIT, it should be input in the following format: " << "\r\n"
			<< "edit <task index> <edit target> <edit informations>" << "\r\n"
			<< "1. edit 000001 des physics homework" << "\r\n"
			<< "2. edit 000002 date 13 march" << "\r\n"
			<< "3. edit 000003 time 2pm" << "\r\n"
			<< "4. edit 000004 prior low" << "\r\n"
			<< "the function will edit the task specified with the task index and then modified the categories of the task accordingly."
			<< "\r\n";
	}
	else if (desireCommand == "directory"){
		oss << "To CHANGE DIRECTORY, it should be input in the following format: " << "\r\n"
			<< "directory <new file directory>" << "\r\n"
			<< "1. directory D:\\savefile.txt"
			<< "\r\n";
	}
	else if (desireCommand == "sort"){
		oss << "To use SORT, it should be input in the following format: " << "\r\n"
			<< "sort by <criteria>" << "\r\n"
			<< "1. sort by date" << "\r\n"
			<< "2. sort by priority"
			<< "\r\n";
	}
	else if (desireCommand == "mark"){
		oss << "To use MARK, it should be input in the following format: " << "\r\n"
			<< "mark <index number>" << "\r\n"
			<< "Exampe of using this command: " << "\r\n"
			<< "1. mark 020300" << "\r\n"
			<< "Executing this command will change the status of the task to done." << "\r\n"
			<< "\r\n";
	}
	else{
		return MESSAGE_INVALID_HELP;
	}

	return oss.str();
}

string ExecuteHelp::undo() {
	return "";
}