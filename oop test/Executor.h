#pragma once
#include "Global.h"
#include "UserTask.h"
#include "Storage.h"
#include "ExtDataBase.h"

class Executor {
public:
	virtual string execute(Storage&, ExtDataBase, vector<list<StickyNote>::iterator>&, bool&) = 0;
	virtual string undo() = 0;

	virtual ~Executor() = 0;
};

inline Executor::~Executor() { };