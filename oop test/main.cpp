#include "Global.h"
#include "Logic.h"

//@author A0108341R
int main() {

	Logic* logic = new Logic;
	bool edited = false;

	while (true) {

		string input;
		string result;
		bool successful = false;
		getline(cin, input);
		result = logic->handleInput(input, edited, successful);
		cout << result;

	}

	return 0;
}