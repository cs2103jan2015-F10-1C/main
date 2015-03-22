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
	string oneTaskInfoTypeOne(list<StickyNote>::iterator);
	string oneTaskInfoTypeTwo(list<StickyNote>::iterator);

};

