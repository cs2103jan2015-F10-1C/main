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