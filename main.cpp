#include <string>
#include <iostream>
#include <fstream>

#include "board.h"

using namespace std;


int main(int argc, char** argv) {

	if (argc < 2) {
		cout << "ERROR!" << endl << \
		"The correct format is: <exec-name> <input-file>" << endl;
		return 1;
	}

	cout << "You have entered ";
	for (int i = 0; i < argc; i++) {
		cout << argv[i] << " ";
	}
	cout << endl;

	// opens the input file provided by user and creates board object
	ifstream in_file(argv[1]);
	Board b(in_file);


	return 0;
}

