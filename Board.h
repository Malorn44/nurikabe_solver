#ifndef _BOARD_H_
#define _BOARD_H_

#include <string>
#include <vector>
#include <iostream>


using namespace std;

// For storing the nurikabe board and doing operations upon it.
class Board {
	public:
		// Default Constructor
		Board();

		// Prints out the board
		void print() const;

	private:
		// Structure for holding the board
		vector<vector<int> > board;
		int height;
		int width;
};

#endif