#include "Global.h"
#include "Logic.h"


int main() {

	Logic* logic = new Logic;
	bool edited = false;
	bool successful;

	while (true) {
		successful = false;
		string input;
		string result;
		getline(cin, input);
		result = logic->handleInput(input, edited, successful);
		cout << result;

	}


	return 0;
}