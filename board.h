#ifndef _BOARD_H_
#define _BOARD_H_

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "../libs/pugixml/src/pugixml.hpp"

using namespace std;

// For parsing an xml file used to store a puzzle
class Board {
	public:
		Board(ifstream& file);

		vector<vector<int> > fileToVector();

	private:
}








#endif
