#pragma once
#include "Global.h"
#include "StickyNote.h"


class Storage : public StickyNote {
private: 
	list<StickyNote> _noteBook;
public:
	Storage();
	~Storage();
	string addNewNote(StickyNote);
	list<StickyNote>::iterator getIter();
	bool erase(list<StickyNote>::iterator);
	int getSize();
	int getSameDateCount(string);
	bool noRepeatIndexCount(string);
	bool checkClashExist(list<StickyNote>::iterator, list<StickyNote>::iterator);
	bool checkInitialCondition(list<StickyNote>::iterator, list<StickyNote>::iterator);
	bool checkTimeClash(list<StickyNote>::iterator iter, list<StickyNote>::iterator);
	bool checkNoteClashExist(list<StickyNote>::iterator iter, StickyNote& note);
	bool checkNoteInitialCondition(list<StickyNote>::iterator, StickyNote&);
	bool checkNoteTimeClash(list<StickyNote>::iterator, StickyNote&);
	bool checkIterClashExists(list<StickyNote>::iterator, list<StickyNote>::iterator);
	bool checkIterInitialCondition(list<StickyNote>::iterator, list<StickyNote>::iterator);
	bool checkIterTimeClash(list<StickyNote>::iterator, list<StickyNote>::iterator);
	string oneTaskInfoTypeOne(list<StickyNote>::iterator);
	string oneTaskInfoTypeTwo(list<StickyNote>::iterator);
	void findClashes();
	void findClashes(StickyNote&);
	void findClashes(list<StickyNote>::iterator);
};

