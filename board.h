#ifndef _BOARD_H_
#define _BOARD_H_

#include <string>
#include <vector>
#include <fstream>
#include <iostream>


using namespace std;

// For storing the nurikabe board and doing operations upon it.
class Board {
	public:
		// Default Constructor
		Board(ifstream& file);

		// Constructor Helpers
		void fileToVector(ifstream& file);

		// Prints out the board
		void print() const;

	private:
		// Structure for holding the board
		vector<vector<int> > board;
		int height;
		int width;

		// Structure for holding the value of cells
		vector<vector<int> > cellval;
};

#endif