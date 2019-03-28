#ifndef _BOARD_H_
#define _BOARD_H_

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "tinyxml2/tinyxml2.h"

using namespace std;

// for use in parsing the XML file
struct Cell {
	int value;
	int x;
	int y;
};

// For parsing an xml file used to store a puzzle
class Board {
	public:
		// Contructor
		Board(string& file);
		void createNewBoard(string& file);
		
		// Prints
		void print();

	private:
		vector<Cell> ParseXML(string& file);

		// Member variables
		vector<vector<int> > board;
		int height;
		int width;
};

#endif
