#ifndef _BOARD_H_
#define _BOARD_H_

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "tinyxml2/tinyxml2.h"


using namespace std;

struct Cell {
	int value;
	int x;
	int y;
};

// For parsing an xml file used to store a puzzle
class Board {
	public:
		Board(string& file);
		void createNewBoard(string& file);
		void print();

	private:
		vector<Cell> ParseXML(string& file);

		vector<vector<int> > board;
		int height;
		int width;
};



#endif
