#include "StickyNote.h"


StickyNote::StickyNote(void)
{
}


StickyNote::~StickyNote(void)
{
}
//@author A0108375A
void StickyNote::setEverything(string details, string date, string time, string priority, string index) {

	_details = details;
	_date = date;
	_time = time;
	_priority = priority;
	_index = index;

}

// GETTERS

//@author A0108375A

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

//@author A0110748J
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

//@author A0108341R
void StickyNote::setDay(int day){
	_day = day;
}
void StickyNote::setMonth(int month){
	_month = month;
}

void StickyNote::setStartTime(int startH, int startM) {
	ostringstream oss;
	oss << startH << ":" << startM;
	_sStartTime = oss.str();
}

void StickyNote::setEndTime(int endH, int endM) {
	ostringstream oss;
	oss << endH << ":" << endM;
	_sEndTime = oss.str();
}

void StickyNote::setDetails(string change) {
	_details = change;
}

//@author A0093863U
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
