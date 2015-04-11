#include "ExecuteHelp.h"


ExecuteHelp::ExecuteHelp(UserTask* task) {
	_task = task;
}

ExecuteHelp::~ExecuteHelp()
{
}

//@author A0108375A
string ExecuteHelp::execute(Storage& _storage, ExtDataBase extdb, vector<list<StickyNote>::iterator>& _allItems, bool& successful) {
	ostringstream oss;
	string desireCommand = _task->getRemaining(); 
	
	try{
		if (desireCommand == ""){
			successful = false;
			throw MESSAGE_INVALID_HELP;
		}
	}
	catch (string e){
		return e;
	}

	try{
		if (desireCommand == "add"){

			oss << "Please notice that WiseManager does not support a task between more than 1 days." << "\r\n"
				<< "In other words, the starting time and ending time should be within the same day." << "\r\n"

				<< "To use ADD, it should be input in the following format: " << "\r\n"
				<< "\r\n"
				<< "1. add <details of the task> date time -priority				or" << "\r\n"
				<< "2. add <details of the task> time date -priority				or" << "\r\n"
				<< "3. add <details of the task> <by/before/is/on> time -priority				or" << "\r\n" << "\r\n"
				<< "An example of a simple add task input will be: " << "\r\n"
				<< "1.	add do homework 3 march 5pm -high" << "\r\n"
				<< "2.	add do homework 5pm on 3 march -high" << "\r\n"
				<< "this means adding the task do homework on 3 march at 5pm with high priority" << "\r\n"
				<< "3.	add do homework 3 march 5pm - 5.50pm -high" << "\r\n"
				<< "this means adding the task do homework on 3 march at from 5pm to 5.50pm with high priority" << "\r\n"
				<< "4.	add do homework 5.30pm - 9.30pm tomorrow -high" << "\r\n"
				<< "this means adding the task do homework on the next day from 5.30pm - 9.30pm with high priority" << "\r\n"
				<< "5.	add do homework 11:5 tomorrow -high" << "\r\n"
				<< "this means adding the task do homework on the next day at 11:05 with high priority" << "\r\n"
				<< "please do non enter by 11:05" << "\r\n"
				<< "6.	add do homework by 5pm tomorrow -high" << "\r\n"
				<< "this means adding the task do homework on the next day before 5pm with high priority" << "\r\n"
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
				<< "\r\n"

				<< "1.4	For details with conflicting terms such as certain days in a week and am / pm, user needs to include a quotation mark" << "\r\n"
				<< "\r\n"
				<< "To avoid creating a task on tuesday or at 3pm." << "\r\n"
				<< "e.g.meet at \"taco tuesday\" or meet at \"cafe 3pm\" or \"high tea\"" << "\r\n"
				<< "\r\n"

				<< "1.5	Handling inputs that goes missing" << "\r\n"
				<< "\r\n"
				<< "If there is an empty inputs for example:" << "\r\n"
				<< "UNBOUNDED:" << "\r\n"
				<< "1.[All day event][Status:incomplete]" << "\r\n"
				<< "This means there is input of conflicting terms and user can undo the task and adding the task with quotation marks around the task descriptions." << "\r\n"
				<< "\r\n";
		}
		else if (desireCommand == "display"){

			oss << "To use DISPLAY, it should be input in the following format: " << "\r\n"
				<< "\r\n"
				<< "1. display" << "\r\n"
				<< "2. display week" << "\r\n"
				<< "to display task in one-week period" << "\r\n"
				<< "\r\n"
				<< "\r\n";
		}
		else if (desireCommand == "search"){

			oss << "To use SEARCH, it should be input in the following format: " << "\r\n"
				<< "\r\n"
				<< "search <task description>" << "\r\n"
				<< "the function will then return the tasks with the keywords input by the user. " << "\r\n"
				<< "please take note of the task indexes as displayed on the user interface as they will be used for delete and edit purposes" << "\r\n"
				<< "\r\n";
		}
		else if (desireCommand == "delete"){

			oss << "To use DELETE, it should be input in the following format: " << "\r\n"
				<< "\r\n"
				<< "delete <task index>" << "\r\n"
				<< "\r\n"
				<< "For example:" << "\r\n"
				<< "if the display shows:" << "\r\n"
				<< "1.[All day event] meet junyang[Status:incomplete]" << "\r\n"
				<< "2.[All day event] meet zann[Status:incomplete]" << "\r\n"
				<< "3.[All day event] meet ruyan[Status:incomplete]" << "\r\n"
				<< "\r\n"
				<< "if the user inputs \"delete 1\" " << "\r\n"
				<< "the function will then delete the task with index 1 in display list which is: " << "\r\n"
				<< "1.[All day event] meet junyang[Status:incomplete]" << "\r\n"
				<< "\r\n";
		}
		else if (desireCommand == "edit"){

			oss << "To use EDIT, it should be input in the following format: " << "\r\n"
				<< "edit <task index> <edit informations>" << "\r\n"
				<< "\r\n"
				<< "For example:" << "\r\n"
				<< "if the display shows:" << "\r\n"
				<< "TODAY: " << "\r\n"
				<< "1.[21:00 - 22 : 00] meet zann[Status:incomplete]" << "\r\n"
				<< "\r\n"
				<< "The user can input the following to edit the task: " << "\r\n"
				<< "1. edit 1 meet derrick tomorrow 9pm " << "\r\n"
				<< "\r\n"
				<< "The edited task will be as follows: " << "\r\n"
				<< "TOMORROW:" << "\r\n"
				<< "1.[21:00 - 22 : 00] meet derrick[Status:incomplete]" << "\r\n"
				<< "the function will edit the task specified with the task index and then modified the information of the task accordingly." << "\r\n"
				<< "\r\n"
				<< "To change task from bounded to unbounded: " << "\r\n"
				<< "If the screen displays this: " << "\r\n"
				<< "TOMORROW:" << "\r\n"
				<< "1.[21:00 - 22 : 00] meet derrick[Status:incomplete]" << "\r\n"
				<< "edit 1 99/99 99:99 " << "\r\n"
				<< "This will change the task to unbounded and the screen will appear:  " << "\r\n"
				<< " UNBOUNDED:" << "\r\n"
				<< "1.[All day event] meet derrick" << "\r\n"
				<< "\r\n";
		}
		else if (desireCommand == "directory"){
			oss << "To CHANGE DIRECTORY, it should be input in the following format: " << "\r\n"
				<< "directory <new file directory>" << "\r\n"
				<< "1. directory D:\\\savefile.txt"
				<< "\r\n";
		}
		/*	else if (desireCommand == "sort"){
				oss << "To use SORT, it should be input in the following format: " << "\r\n"
				<< "sort by <criteria>" << "\r\n"
				<< "1. sort by date" << "\r\n"
				<< "2. sort by priority"
				<< "\r\n";
				}
				*/
		else if (desireCommand == "mark"){
			oss << "To use MARK, it should be input in the following format: " << "\r\n"
				<< "\r\n"
				<< "For example:" << "\r\n"
				<< "if the display shows:" << "\r\n"
				<< "TODAY: " << "\r\n"
				<< "1.[21:00 - 22 : 00] meet zann[Status:incomplete]" << "\r\n"
				<< "\r\n"
				<< "To signify Task completion: " << "\r\n"
				<< "user can input in the following format: mark <index number>" << "\r\n"
				<< "Exampe of using this command: " << "\r\n"
				<< "1. mark 1" << "\r\n"
				<< "\r\n"
				<< "Executing this command will change the status of the task to done." << "\r\n"
				<< "Task will be shifted to the archive upon this command and user will no longer see it in the display box." << "\r\n"
				<< "\r\n";
		}
		else if (desireCommand == "undo"){
			oss << "To use UNDO, it should be input in the following format: " << "\r\n"
				<< "This command reverts the programme back to its previous state." << "\r\n"
				<< "\r\n"
				<< "For example:" << "\r\n"
				<< "if the previous action by an user is \"add do homework today 9pm\" " << "\r\n"
				<< "resulting which the display shows:" << "\r\n"
				<< "TODAY: " << "\r\n"
				<< "1.[21:00 - 22 : 00] do homework[Status:incomplete]" << "\r\n"
				<< "\r\n"
				<< "To execute undo for this addition of task: " << "\r\n"
				<< "user can input in the following format: undo" << "\r\n"
				<< "Exampe of using this command: " << "\r\n"
				<< "1. undo" << "\r\n"
				<< "Executing this command will remove the task added previously." << "\r\n"
				<< "\r\n"
				<< "The same applies for mark, edit,delete and change of directory." << "\r\n"
				<< "Nothing will happen if you undo other commands.(i.e search,sort and display) " << "\r\n"
				<< "User will be able to keep using UNDO command till his/her very first action" << "\r\n"
				<< "\r\n";
		}
		else{
			successful = false;
			throw MESSAGE_INVALID_HELP;
		}
	}
	catch (string e){
		return e;
	}

	successful = true;

	return oss.str();
}

string ExecuteHelp::undo() {

	return "";
}
