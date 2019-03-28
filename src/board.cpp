#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <iostream>

#include "board.h"

using namespace tinyxml2;

void printCell (const Cell& cell) {
	std::cout << "Cell{value: " << cell.value << " x: " << cell.x << " y: " << cell.y << " }" << std::endl;
}

// Constructor
Board::Board(string& file) {
	height = 0;
	width = 0;
	createNewBoard(file);
}

// Constructor helper, initializes the board matrix with the propper values
void Board::createNewBoard(string& file) {
	std::vector<Cell> cellVec = ParseXML(file);	

	for (int i = 0; i < height; i++) {
		board.push_back(std::vector<int>());
		for (int j = 0; j < width; j++) {
			board[i].push_back(0);
		}
	}

	for (const Cell& c : cellVec) {
		board[c.y][c.x] = c.value;
	}

}

// Prases the XML file using tinyxml2 and returns a vector of Cells that have
// a value defined in the XML file. Also sets the height and width values or board
// when it encounters that information. Has some minor error checking, if it finds an
// error it returns an empty vector<Cell>
std::vector<Cell> Board::ParseXML(string& file) {

	XMLDocument doc;
	bool invalidFile = doc.LoadFile(file.c_str());

	if (invalidFile) {
		std::cout << "Error! File not found." << endl;
		return std::vector<Cell>();
	}

	const XMLElement* puzzle = doc.FirstChildElement("Legup")->FirstChildElement("puzzle");
	// const XMLElement* puzzle = legup->FirstChildElement("puzzle");
	const std::string puzzleName(puzzle->Attribute("name"));
	const XMLElement* board = puzzle->FirstChildElement("board");
	const std::string h(board->Attribute("height"));
	const std::string w(board->Attribute("width"));
	const XMLElement* cell = board->FirstChildElement("cells")->FirstChildElement("cell");

	std::vector<Cell> cellVec;

	// if the puzzleName is not Nurikabe then we have an incorrect puzzle.
	if (puzzleName != "Nurikabe") {
		std::cout << "Invalid puzzle file! This program only acceps Nurikabe puzzles." << endl;
		return cellVec;
	}

	height = std::stoi(h);
	width = std::stoi(w);

	while (cell != nullptr) {
		Cell c;
		c.value = std::stoi(cell->Attribute("value"));
		c.x = std::stoi(cell->Attribute("x"));
		c.y = std::stoi(cell->Attribute("y"));
		cellVec.push_back(c);

		cell = cell->NextSiblingElement("cell");
	}

	std::cout << "Puzzle read!" << std::endl;
	std::cout << "Puzzle name: " << puzzleName << std::endl;
	std::cout << "Board height: " << height << " width: " << width << std::endl;
	std::cout << "Cells: " << std::endl;
	for (const Cell& c : cellVec) {
		printCell(c);
	}

	return cellVec;
}

// Prints out the board with spaces for separation
// Will look odd for numbers with >= 2 digits
void Board::print() {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (board[i][j] == 0) {
				std::cout << ". ";
			} else {
				std::cout << board[i][j] << " ";
			}
		}
		std::cout << std::endl;
	}
}
