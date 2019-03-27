#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "tinyxml2/tinyxml2.h"

using namespace tinyxml2;

class Cell {
	std::string value;
	std::string x;
	std::string y;
public:
	Cell(std::string _value, std::string _x, std::string _y) :
	value(std::move(_value)),
	x(std::move(_x)),
	y(std::move(_y)) {}

	const std::string& getValue() { return value; }
	const std::string& getX() { return x; }
	const std::string& getY() { return y; }

	friend std::ostream& operator<< (std::ostream& os, const Cell& cell);

};

std::ostream& operator<< (std::ostream& os, const Cell& cell) {
	os << "Cell{value: " << cell.value << " x: " << cell.x << " y: " << cell.y << " }";
	return os;
}

int main(int argc, char** argv) {

	if (argc != 2) {
		std::cout << "Need to supply an xml file!" << std::endl;
		return 1;
	}
	assert(argc > 1);
	XMLDocument doc;
	doc.LoadFile(argv[1]);
	const auto legup = doc.FirstChildElement("Legup");
	const auto puzzle = legup->FirstChildElement("puzzle");
	const std::string puzzleName(puzzle->Attribute("name"));
	const auto board = puzzle->FirstChildElement("board");
	const std::string height(board->Attribute("height"));
	const std::string width(board->Attribute("width"));
	const auto cells = board->FirstChildElement("cells");

	auto cell = cells->FirstChildElement("cell");

	std::vector<Cell> cellVec;

	while (cell != nullptr) {
		std::string val(cell->Attribute("value"));
		std::string x(cell->Attribute("x"));
		std::string y(cell->Attribute("y"));
		cellVec.push_back(Cell(val, x, y));

		cell = cell->NextSiblingElement("cell");
	}

	std::cout << "Puzzle read!" << std::endl;
	std::cout << "Puzzle name: " << puzzleName << std::endl;
	std::cout << "Board height: " << height << " width: " << width << std::endl;
	std::cout << "Cells: " << std::endl;
	for (const Cell& c : cellVec) {
		std::cout << c << std::endl;
	}

	return 0;
}