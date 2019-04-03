#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "tinyxml2/tinyxml2.h"
#include "nurikabe.h"

using namespace std;

struct Cell {
	int value;
	int x;
	int y;
};

void printCell (const Cell& cell) {
	std::cout << "cell {value: " << cell.value << " x: " << cell.x << " y: " << cell.y << " }" << std::endl;
}

// Prases the XML file using tinyxml2 and returns a vector of Cells that have
// a value defined in the XML file. Also sets the height and width values or board
// when it encounters that information. Has some minor error checking, if it finds an
// error it returns an empty vector<Cell>
std::vector<Cell> ParseXML(string& file, int &height, int &width) {
	using namespace tinyxml2;

	XMLDocument doc;
	bool invalidFile = doc.LoadFile(file.c_str());

	// If the file couldn't be loaded we print an error message.
	if (invalidFile) {
		std::cerr << "Error! File not found." << endl;
		return std::vector<Cell>();
	}

	const XMLElement* puzzle = doc.FirstChildElement("Legup")->FirstChildElement("puzzle");
	const std::string puzzleName(puzzle->Attribute("name"));
	const XMLElement* board = puzzle->FirstChildElement("board");
	const std::string h(board->Attribute("height"));
	const std::string w(board->Attribute("width"));
	const XMLElement* cell = board->FirstChildElement("cells")->FirstChildElement("cell");

	std::vector<Cell> cellVec;

	// if the puzzleName is not Nurikabe then we have an incorrect puzzle.
	if (puzzleName != "Nurikabe") {
		std::cerr << "Invalid puzzle file! This program only acceps Nurikabe puzzles." << endl;
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

// takes the cell vector created by ParseXML and turns it into a string format
// readable by the auto solver (after it is put into a Puzzle object)
string puzzleToString(vector<Cell> &cellVec, int &height, int &width) {
	string output = "";
	bool placedNum = false;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			for (int k = 0; k < cellVec.size(); k++) {
				if (cellVec[k].y == i && cellVec[k].x == j) {
					output += to_string(cellVec[k].value);
					cellVec.erase(cellVec.begin() + k);
					placedNum = true;
					break;
				}
			}
			if (!placedNum) {
				output += " "; 
			}
			placedNum = false;
		}
		output += "\n";
	}
	return output;
}

int main(int argc, char** argv) {

	if (argc != 2) {
		cerr << "Need to supply an xml file!" << endl;
		return 1;
	}

    struct Puzzle {
        const char * name;
        int w;
        int h;
        const char * s;
    };

    int height = 0;
    int width = 0;
    string file = argv[1];
    vector<Cell> cellVec = ParseXML(file, height, width);

    // catches error indiciated by empty reuturn vector
    if (cellVec.empty()) {
    	return 1;
    }

    // converting to Puzzle object readable by the solver
    Puzzle puzzle;
    puzzle.h = height;
    puzzle.w = width;
    size_t last = file.find_last_of("/");
    if (last != string::npos) file = file.substr(last+1);
    puzzle.name = file.c_str();
    string out = puzzleToString(cellVec, height, width);
    puzzle.s = out.c_str();


    try {
        const auto start = steady_clock::now();

        Grid g(puzzle.w, puzzle.h, puzzle.s);

        while (g.solve() == Grid::KEEP_GOING) { }

        const auto finish = steady_clock::now();


        ofstream f(string("html-output/") + puzzle.name + string(".html"));

        g.write(f, start, finish);


        cout << puzzle.name << ": " << format_time(start, finish) << ", ";

        const int k = g.known();
        const int cells = puzzle.w * puzzle.h;

        cout << k << "/" << cells << " (" << k * 100.0 / cells << "%) solved" << endl;
    } catch (const exception& e) {
        cerr << "EXCEPTION CAUGHT! \"" << e.what() << "\"" << endl;
        return EXIT_FAILURE;
    } catch (...) {
        cerr << "UNKNOWN EXCEPTION CAUGHT!" << endl;
        return EXIT_FAILURE;
    }
}
