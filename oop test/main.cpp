#include "Global.h"
#include "Logic.h"


int main() {

	Logic* logic = new Logic;
	bool edited = false;

	while (true) {

		string input;
		string result;
		getline(cin, input);
		result = logic->handleInput(input, edited);
		cout << result;

	}


	return 0;
}