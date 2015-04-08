#pragma once
#include "Global.h"
#include "Storage.h"
#include "UserTask.h"

class ExtDataBase {
private:
	string _currentLocation;
	string _name;

public:
	ExtDataBase();
	~ExtDataBase();

	string getLocation();
	string setLocation(Storage&, string, bool&);
	void autoSave(Storage&);
	vector<string>* getContent();
	void archive(string);

};