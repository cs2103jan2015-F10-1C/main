#include "Storage.h"


Storage::Storage()
{
}


Storage::~Storage()
{
}

string Storage::addNewNote(StickyNote note) {
	
	findClashes(note);
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
	oss << "[ ";

	if (iter->getPriority() == "high") {
		oss << "high priority, ";
	}
	
	if (iter->getCategory() == "Deadline") {
		oss << "Before ";
	}
	if (iter->getStartTime() == 0) {
		oss << iter->getTime();
	}
	else {
		oss << iter->getSStartTime();
		if (iter->getCategory() != "Deadline") {
			oss << "-" << iter->getSEndTime();
		}
	}
	oss << " ] " << iter->getDetails(); 
	if (iter->getStatus() == "Clash" || iter->getStatus() == "cleared") {
		oss << " [" << iter->getStatus() << "] ";
	}
	oss << "\r\n";
	return oss.str();

}

string Storage::oneTaskInfoTypeTwo(list<StickyNote>::iterator iter) {
	ostringstream oss;
	string details = iter->getDetails();
	int startingPos = details.find_first_not_of(" ");
	if (startingPos >= 0){
		details = details.substr(startingPos);
	}
	oss << "\"" <<  details << "\""<< " ";
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
	else {
		oss << "-none";
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

void Storage::findClashes() {

	int _size = getSize();
	list<StickyNote>::iterator iter;
	iter = getIter();

	for (int i = 0; i < _size; i++, iter++) {
		bool isClashExist = false;
		if (iter->getStatus() == "Clash") {
			list<StickyNote>::iterator find;
			find = getIter(); // i do not want to increment iter.
			for (int j = 0; j < _size; j++, find++) {
				if (checkClashExist(iter, find)){
					isClashExist = true;
					break;
				}
			}
		}
		if (!isClashExist) {
			iter->setStatus("incomplete");
		}
	}
}


void Storage::findClashes(StickyNote& note) {

	int _size = getSize();
	list<StickyNote>::iterator iter;
	iter = getIter();

	for (int i = 0; i < _size; i++, iter++) {
		if (checkNoteClashExist(iter, note)) {
			note.setStatus("Clash");
			iter->setStatus("Clash");
		}
	}

}


void Storage::findClashes(list<StickyNote>::iterator iter) {

	int _size = getSize();
	list<StickyNote>::iterator S_iter;
	S_iter = getIter();

	for (int i = 0; i < _size; i++, S_iter++) {
		if (checkIterClashExists(iter, S_iter)) {
			iter->setStatus("Clash");
			S_iter->setStatus("Clash");
		}
	}
}


bool Storage::checkClashExist(list<StickyNote>::iterator iter, list<StickyNote>::iterator find){

	bool clash = false;
	if (checkInitialCondition(iter, find)) {
		if (checkTimeClash(iter, find)) {
			clash = true;
		}
	}

	return clash;
}

bool Storage::checkInitialCondition(list<StickyNote>::iterator iter, list<StickyNote>::iterator find){
	return ((iter->getDate() == find->getDate()) &&
		find->getStartTime() != 0 &&
		find->getEndTime() != 0 &&
		find->getStatus() == "Clash" &&
		(find->getIndex() != iter->getIndex()));
}

bool Storage::checkTimeClash(list<StickyNote>::iterator iter, list<StickyNote>::iterator find){
	return (!(iter->getStartTime() > find->getStartTime() &&
		iter->getStartTime() >= find->getEndTime()) &&
		!(iter->getEndTime() <= find->getStartTime() &&
		iter->getEndTime() < find->getEndTime()));
}

bool Storage::checkNoteClashExist(list<StickyNote>::iterator iter, StickyNote& note){

	bool clash = false;
	if (checkNoteInitialCondition(iter, note)) {
		if (checkNoteTimeClash(iter, note)) {
			clash = true;
		}
	}
	return clash;
}

bool Storage::checkNoteInitialCondition(list<StickyNote>::iterator iter, StickyNote& note){
	return ((note.getDate() == iter->getDate()) &&
		iter->getStartTime() != 0 &&
		iter->getEndTime() != 0 &&
		iter->getStatus() != "cleared");
}

bool Storage::checkNoteTimeClash(list<StickyNote>::iterator iter, StickyNote& note){
	return (!(note.getStartTime() > iter->getStartTime() &&
		note.getStartTime() >= iter->getEndTime()) &&
		!(note.getEndTime() <= iter->getStartTime() &&
		note.getEndTime() < iter->getEndTime()));
}

bool Storage::checkIterClashExists(list<StickyNote>::iterator iter, list<StickyNote>::iterator S_iter){

	bool clash = false;
	if (checkIterInitialCondition(iter, S_iter)) {
		if (checkIterTimeClash(iter, S_iter)){
			clash = true;
		}
	}
	return clash;
}

bool Storage::checkIterInitialCondition(list<StickyNote>::iterator iter, list<StickyNote>::iterator S_iter){
	return ((iter->getDate() == S_iter->getDate()) &&
		S_iter->getStartTime() != 0 &&
		S_iter->getEndTime() != 0 &&
		S_iter->getStatus() != "cleared" &&
		(iter->getIndex() != S_iter->getIndex()));
}

bool Storage::checkIterTimeClash(list<StickyNote>::iterator iter, list<StickyNote>::iterator S_iter){
	return (!(iter->getStartTime() > S_iter->getStartTime() &&
		iter->getStartTime() >= S_iter->getEndTime()) &&
		!(iter->getEndTime() <= S_iter->getStartTime() &&
		iter->getEndTime() < S_iter->getEndTime()));
}