#include "Storage.h"


Storage::Storage()
{
}


Storage::~Storage()
{
}

string Storage::addNewNote(StickyNote note) {
	_noteBook.push_back(note);
	return MESSAGE_ADD;
}

list<StickyNote>::iterator Storage::getIter() {
	return _noteBook.begin();
}

bool Storage::erase(list<StickyNote>::iterator iter) {
	int oldSize, newSize;
	oldSize = _noteBook.size();
	_noteBook.erase(iter);
	newSize = _noteBook.size();

	if (newSize == oldSize - 1) {
		return true;
	}
	return false;
}

int Storage::getSize() {
	return _noteBook.size();
}

int Storage::getSameDateCount(string date) {

	list<StickyNote>::iterator iter;
	iter = _noteBook.begin();
	int size = _noteBook.size();
	int i = 0;
	int count = 0;
	for (iter; i < size; i++, iter++) {
		if (iter->getDate() == date) {
			count++;
		}
	}
	return count;
}

string Storage::oneTaskInfoTypeOne(list<StickyNote>::iterator iter) {

	ostringstream oss;
	oss << "Index: " << iter->getIndex() << "\r\n"
		<< "Details: " << iter->getDetails() << "\r\n"
		<< "Date: " << iter->getDate() << "\r\n"
		<< "Time: " << iter->getTime() << "\r\n"
		<< "Priority: " << iter->getPriority() << "\r\n";
	return oss.str();

}

string Storage::oneTaskInfoTypeTwo(list<StickyNote>::iterator iter) {
	ostringstream oss;

	oss << "\"" << iter->getDetails() << "\""<< " ";
	if (iter->getDate() != "unbounded event") {
		oss << iter->getDate() << " ";
	}
	else {
		oss << "99/99" << " ";
	}
	if (iter->getTime() != "All day event") {
		oss << iter->getTime() << " ";
	}
	else {
		oss << "99:99" << " ";
	}
	if (iter->getPriority() != "") {
		oss << "-" << iter->getPriority(); 
	}
		oss << "\n";
		//<< "\r\n";
	return oss.str();
}

bool Storage::noRepeatIndexCount(string index) {

	list<StickyNote>::iterator iter;
	iter = _noteBook.begin();

	for (size_t i = 0; i < _noteBook.size(); i++, iter++) {
		if (iter->getIndex() == index) {
			return false;
		}
	}
	return true;

}
