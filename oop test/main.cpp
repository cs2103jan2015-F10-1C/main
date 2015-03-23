#include "Global.h"
#include "Logic.h"


int main() {

	Logic* logic = new Logic;

	while (true) {

		string input;
		string result;
		getline(cin, input);
		result = logic->handleInput(input);
		cout << result;

	}


	return 0;
}