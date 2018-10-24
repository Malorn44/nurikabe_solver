#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <iostream>

#include "board.h"

using namespace std;

Board::Board(ifstream& file) {
	fileToVector(file);
}

// Intitialize board vector
// Takes input file and adds the integers to vector
void Board::fileToVector(ifstream& file) {
	// counters for determining w and h
	int r = 0;
	int c = 0;

	// read in by line to get height
	string line = "";
	while (getline(file,line)) {
		string word = "";
		stringstream l(line);
		c = 0;
		while (l >> word) {
			// push back empty vector and then push back int
			board.push_back(vector<int>());
			board[r].push_back(atoi(word.c_str()));
			c++;
		}
		r++;
	}
	height = r;
	width = c;
}

void Board::print() const {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (board[i][j] > 0) cout << board[i][j] << " ";
			else cout << "+ ";
		}
		cout << endl;
	}
}
