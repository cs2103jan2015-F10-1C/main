#pragma once
#include "Global.h"
#include "Storage.h"
#include "UserTask.h"

class ExtDataBase {
private:
	string _currentLocation;

public:
	ExtDataBase();
	~ExtDataBase();

	string getLocation();
	string setLocation(Storage&, string);
	void autoSave(Storage&);
	vector<string>* getContent();

};