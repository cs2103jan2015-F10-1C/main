#pragma once
#include "Global.h"
#include "Standardise.h"
#include "Date.h"
#include "Storage.h"


class HandleInput {
private:
	bool isSpecialDetail(string);
	bool isPriority(string);
	bool isTime(string);
	bool isBuffer(string);
	bool isDeadline(string);

public:
	HandleInput(void);
	~HandleInput(void);

	void handle(string input, string&, string&, string&, string&, string&, string&, bool&, Storage&);
	string getIndex(string, Storage);


};

