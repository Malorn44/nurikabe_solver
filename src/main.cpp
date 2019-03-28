#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "board.h"

using namespace std;

int main(int argc, char** argv) {

	if (argc != 2) {
		std::cout << "Need to supply an xml file!" << std::endl;
		return 1;
	}
	string file = argv[1];
	Board b(file);

	b.print();

	return 0;
}
