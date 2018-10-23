#include <string>
#include <iostream>

using namespace std;


int main(int argc, char** argv) {

	if (argc < 2) {
		cout << "ERROR!" << endl << \
		"The correct format is: <exec-name> <input-file>" << endl;
	}

	cout << "You have entered ";
	for (int i = 0; i < argc; i++) {
		cout << argv[i] << " ";
	}
	cout << endl;


	return 0;
}

