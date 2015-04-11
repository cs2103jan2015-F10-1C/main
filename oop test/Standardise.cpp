#include "Standardise.h"


Standardise::Standardise() 
{

}

Standardise::~Standardise() 
{
}

//@author A0110748J
string Standardise::standardiseDate(string date) {
	string standardisedDate;
	string extract;
	istringstream iss(date);
	string day_extract = "";
	string month_extract = "";
	
	// get current date
	time_t rawTime;
	struct tm * timeInfo = new struct tm;

	time(&rawTime);
	localtime_s(timeInfo, &rawTime);

	int day = timeInfo->tm_mday;
	int month = timeInfo->tm_mon + 1;
	int year = timeInfo->tm_year + 1900;
	int wDay = timeInfo->tm_wday;

	// info arrays
	int daysInMth[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	string mthsInYr[12] = { "jan", "feb", "mar", "apr", "may", "jun", "jul", "aug", "sep", "oct", "nov", "dec" };
	string dayInWeek[7] = { "monday", "tuesday", "wednesday", "thursday", "friday", "saturday", "sunday" };
	string others[2] = { "today", "tomorrow" };
	string controls[2] = { "next", "this" };

	// start standardising
	if (date.empty()) {
		return "unbounded event";
	}

	if (date == "unbounded event") {
		return date;
	}

	if (date == "99/99") {
		return "unbounded event";
	}

	while (iss) {

		bool identified = false;
		iss >> extract;

		if (!iss){
			break;
		}

		if (!identified) {
											// case already in standardised form
			int found = -1;
			found = extract.find('/');
			if (found > 0) {
				int posOfSlash = extract.find_first_of('/', 0);
				string sday = extract.substr(0, posOfSlash);
				string smonth = extract.substr(posOfSlash + 1);
				day = atoi(sday.c_str());
				month = atoi(smonth.c_str());
				identified = true;
			}
		}

		if (!identified) {
			int numberOfDays = 2; 			// case today or tomorrow
			for (size_t case1 = 0; case1 < numberOfDays; case1++) {
				if (extract == others[case1]) {
					day = day + case1;
					identified = true;
				}
			}
		}

		if (!identified) {
			int numberOfDays = 2;			// case next / this
			for (size_t case2 = 0; case2 < numberOfDays; case2++) {
				if (extract == controls[case2]) {
					if (case2 == 0) { // if next
						day = day + 7;
						identified = true;
					}
											// if this, do nothing
					identified = true;
				}
			}
		}

		if (!identified) {
			int numberOfDays = 7;			// case day of week
			for (size_t case3 = 0; case3 < numberOfDays; case3++) {
				if (extract == dayInWeek[case3]) {
					int inputDay = case3 + 1; // 1: monday, 2: tuesday ... 7: sunday
					int diff;				// used to calculate the number of days difference between current day and input day.
					if (inputDay <= wDay) {
						inputDay = inputDay + numberOfDays;
					}
					diff = inputDay - wDay;
					day = day + diff;
					identified = true;
				}
			}
		}

		if (!identified) {
											// case specific date e.g. 3rd march, this function extracts the numerical day.
			for (size_t case4 = 0; case4 < extract.length(); case4++) {
				if (extract[case4] >= '0' && extract[case4] <= '9') {
					day_extract = day_extract + extract[case4];
					identified = true;
				}
			}
		}

		if (!identified) {
			int numberOfMonth = 12;			// case month
			extract[0] = tolower(extract[0]); // to change Month to month
			for (size_t case5 = 0; case5 < numberOfMonth; case5++) {
				int found = -1;
				found = extract.find(mthsInYr[case5]);
				if (found >= 0) {
					month_extract = to_string(case5 + 1);
					identified = true;
					break;
				}
			}
		}


	}// end while (iss)

	// check for day validity
	if (day > daysInMth[month - 1]) {
		day = day - daysInMth[month - 1];
		month++;
	}

	if (day_extract == "") {
		day_extract = to_string(day);
	}
	if (month_extract == "") {
		month_extract = to_string(month);
	}

	standardisedDate = day_extract + "/" + month_extract;

	return standardisedDate;
}

//@author A0093863U
string Standardise::standardiseTime(string inputTime) {
	if (inputTime.empty()) { // for no time input by user
		return "All day event";
	}

	if (inputTime == "All day event") {
		return inputTime;
	}

	if (inputTime == "99:99") {
		return "All day event";
	}

	int hour_s;
	int hour_e = 00;
	int min_s = 00;
	int min_e = 00;
	string AmPm;
	string changed;
	string shour_s;
	string shour_e;
	string smin_s;
	string smin_e;

	std::string::size_type sz;
	hour_s = stoi(inputTime, &sz);
	inputTime = inputTime.substr(sz);

	if (inputTime[0] == '.' || inputTime[0] == ':') { // there exists some minutes
		inputTime = inputTime.substr(1);
		min_s = stoi(inputTime, &sz);
		inputTime = inputTime.substr(sz);
	}

	// check for any am / pm attached to start time
	if (inputTime.find("am") == 0) {
		int midnight = 12;
		inputTime = inputTime.substr(2); // remove am
		if (hour_s == midnight) {
			hour_s = 0; // midnight = 00:00
		}
	}
	else if (inputTime.find("pm") == 0) {
		int numberOfHours = 12;
		inputTime = inputTime.substr(2); // remove pm
		if (hour_s < 12) {
			hour_s = hour_s + numberOfHours;
		}
	}

	if (inputTime[0] == '-') { // end time exists
		inputTime = inputTime.substr(1);
		hour_e = stoi(inputTime, &sz);
		inputTime = inputTime.substr(sz);
		if (inputTime[0] == '.' || inputTime[0] == ':') { // there exists some minutes
			inputTime = inputTime.substr(1);
			min_e = stoi(inputTime, &sz);
			inputTime = inputTime.substr(sz);
		}

		// check for any am / pm attached to end time
		if (inputTime.find("am") == 0) {
			int midnight = 12;
			inputTime = inputTime.substr(2); // remove am
			if (hour_e == midnight) {
				hour_e = 0; // midnight = 00:00
			}
		}
		else if (inputTime.find("pm") == 0) {
			int numberOfHours = 12;
			inputTime = inputTime.substr(2); // remove pm
			if (hour_e < 12) {
				hour_e = hour_e + numberOfHours;
			}
		}
	}
	else { // no end time found
		hour_e = hour_s + 1; // create an hour long event
		min_e = min_s;
	}

	// below just makes the 0's appear nicer. in output e.g. 00:00 rather than 0:0
	if (hour_s == 0) {
		shour_s = "00";
	}
	else {
		shour_s = to_string(hour_s);
	}

	if (hour_e == 0) {
		shour_e = "00";
	}
	else {
		shour_e = to_string(hour_e);
	}

	if (min_s == 0) {
		smin_s = "00";
	}
	else if (min_s > 0){
		smin_s = to_string(min_s);
	}

	if (min_e == 0) {
		smin_e = "00";
	}	
	else if (min_e > 0){
		smin_e = to_string(min_e);
	}

	changed = shour_s + ":" + smin_s + "-" + shour_e + ":" + smin_e;

	return changed;
}

//@author A0108375A
string Standardise::standardiseCategory(bool isADeadline, string time) {
	if (isADeadline) {
		return "Deadline";
	}
	else {
		if (time == "All day event") {
			return "unbounded";
		}
		else {
			return "normal";
		}
	}
}

//@author A0108341R
bool Standardise::verifyValidTime(string time){
	try{
		if (time != "All day event" && time != ""){
			int pos1 = time.find_first_of(':');
			int pos2 = time.find_first_of('-');
			int pos3 = time.find_last_of(':');
			int startHr = atoi((time.substr(0, pos1)).c_str());
			int startMin = atoi((time.substr(pos1 + 1, pos2 - (pos1 + 1))).c_str());
			int endHr = atoi((time.substr(pos2 + 1, pos3 - (pos2 + 1))).c_str());
			int endMin = atoi((time.substr(pos3 + 1)).c_str());

				if (!(checkHr(startHr) && checkHr(endHr) && checkMin(startMin) && checkMin(endMin))){
					return false;
				}
				else{
					if (checkCorrectSequence(startHr, endHr, startMin, endMin)){
						return true;
					}
					else{
						return false;
					}
				}
		}
		else{
			throw true;
		}
	}
	catch (bool e){
		return e;
	}
}

//@author A0110748J
bool Standardise::checkHr(int hour){
	try{
		if (hour<0 || hour>23){
			throw false;
		}
		else{
			return true;
		}
	}
	catch (bool e){
		return e;
	}
}

//@author A0110748J
bool Standardise::checkMin(int min){
	try{
		if (min<0 || min>59){
			throw false;
		}
		else{
			return true;
		}
	}
	catch (bool e){
		return e;
	}
}

//@author A0110748J
bool Standardise::checkCorrectSequence(int startHr, int endHr, int startMin, int endMin){
	try{
		if (startHr > endHr){
			throw false;
		}
		else if (startHr < endHr){
			return true;
		}
		else{
			if (startMin >= endMin){
				throw false;
			}
			else{
				return true;
			}
		}
	}
	catch (bool e){
		return e;
	}
}
