#include "StickyNote.h"


StickyNote::StickyNote(void)
{
}


StickyNote::~StickyNote(void)
{
}

void StickyNote::setEverything(string details, string date, string time, string priority, string index) {

	_details = details;
	_date = date;
	_time = time;
	_priority = priority;
	_index = index;

}

// GETTERS

string StickyNote::getCategory() {
	return _category;
}

string StickyNote::getDetails() {
	return _details;

}

string StickyNote::getDate() {
	return _date;

}

string StickyNote::getTime() {
	return _time;

}

string StickyNote::getPriority() {
	return _priority;

}

string StickyNote::getIndex() {
	return _index;
}

int StickyNote::getDay(){
	return _day;
}
int StickyNote::getMonth(){
	return _month;
}

string StickyNote::getStatus(){
	return _status;

}

int StickyNote::getStartTime() {
	return _startTime;
}

int StickyNote::getEndTime() {
	return _endTime;
}

string StickyNote::getSStartTime() {
	return _sStartTime;
}

string StickyNote::getSEndTime() {
	return _sEndTime;
}

// SETTERS

void StickyNote::setDay(int day){
	_day = day;
}
void StickyNote::setMonth(int month){
	_month = month;
}

void StickyNote::setStartTime(int start) {
	_startTime = start;
	_sStartTime = to_string(start);
	if (_sStartTime.size() == 4) {
		_sStartTime.insert(2, ":");
	}
	else if (_sStartTime.size() == 3) {
		_sStartTime.insert(1, ":");
	}
}

void StickyNote::setEndTime(int end) {
	_endTime = end;
	_sEndTime = to_string(end);
	if (_sEndTime.size() == 4) {
		_sEndTime.insert(2, ":");
	}
	else if (_sEndTime.size() == 3) {
		_sEndTime.insert(1, ":");
	}
}

void StickyNote::setDetails(string change) {
	_details = change;
}

void StickyNote::setDate(string change) {
	_date = change;

}

void StickyNote::setTime(string change) {
	_time = change;

}

void StickyNote::setPriority(string change) {
	_priority = change;

}

void StickyNote::setCategory(string change) {
	_category = change;
}

void StickyNote::setIndex(string change) {
	_index = change;
}

void StickyNote::setStatus(string change) {
	_status = change;
}
