#pragma once
#include "Global.h"
#include "Storage.h"
#include "Parser.h"
#include "Executor.h"
#include "ExecuteAdd.h"
#include "ExecuteDelete.h"
#include "ExecuteEdit.h"
#include "ExecuteSearch.h"
#include "ExecuteDisplay.h"
#include "ExecuteDropDown.h"
#include "ExecuteHelp.h"
#include "ExtDataBase.h"
#include "ExecuteDirectory.h"

class Logic
{
private:
	Storage _storage;
	Parser* _parser; 
	stack<Executor*> _inputHistory;
	Executor* dispatch(UserTask*);
	ExtDataBase _extdb;



public:
	Logic();
	~Logic();
	string handleInput(string);
	void initialise();
	string getCurrentDirectory();

};

