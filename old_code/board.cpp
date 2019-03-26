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
			cellval.push_back(vector<int>());
			board[r].push_back(atoi(word.c_str()));

			// pushes back a 1 or a 0 to cellval matrix
			cellval[r].push_back(!!atoi(word.c_str()));
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
			else if (cellval[i][j] == 1) cout << "O ";
			else if (cellval[i][j] == 0) cout << "? ";
			else if (cellval[i][j] == -1) cout << "+ ";
		}
		cout << endl;
	}
}

int Board::countAdjWhite(int r, int c) const {
	int count = 0;
	if (r > 0) count += cellval[r-1][c];
	if (c > 0) count += cellval[r][c-1];
	if (r < height-1) count += cellval[r+1][c];
	if (c < width-1)  count += cellval[r][c+1];
	return count;
}

// NAIVE SOLVERS //

/* Fills in black around a 1
OOO     O+O
O1O --> +1+
OOO     O+O 
*/
void Board::islandOfOne() {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (board[i][j] == 1) {
				if (i > 0) cellval[i-1][j] = -1;
				if (j > 0) cellval[i][j-1] = -1;
				if (i < height-1) cellval[i+1][j] = -1;
				if (j < width-1)  cellval[i][j+1] = -1;
			}
		}
	}
}

void Board::adjacentNum() {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (cellval[i][j] == 0) {
				if (countAdjWhite(i,j) > 1) {
					cellval[i][j] = -1;
				}
			}
		}
	}
}
