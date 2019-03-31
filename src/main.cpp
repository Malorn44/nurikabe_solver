#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "board.h"
#include "nurikabe.h"

using namespace std;


// auto solve board
int solve(Board &b) {
	for (int i = 0; i < b.numRows(); i++) {
		for (int j = 0; j < b.numCols(); j++) {
			if (b.get(i,j) == 1) {
				b.surroundInBlack(i, j);
			}
			if (b.get(i,j) == 0 && b.adjNumbers(i,j) > 1) {
				b.set(i,j,-1);
			}
		}
	}
}

// int main(int argc, char** argv) {

// 	if (argc != 2) {
// 		std::cout << "Need to supply an xml file!" << std::endl;
// 		return 1;
// 	}
// 	string file = argv[1];
// 	Board b(file);

// 	b.print();

// 	solve(b);
// 	// recurse(b, 0);

// 	b.print();

// 	return 0;
// }

string format_tim(const steady_clock::time_point start, const steady_clock::time_point finish) {
    ostringstream oss;

    if (finish - start < 1ms) {
        oss << duration_cast<duration<double, micro>>(finish - start).count() << " microseconds";
    } else if (finish - start < 1s) {
        oss << duration_cast<duration<double, milli>>(finish - start).count() << " milliseconds";
    } else {
        oss << duration_cast<duration<double>>(finish - start).count() << " seconds";
    }

    return oss.str();
}

int main() {
    struct Puzzle {
        const char * name;
        int w;
        int h;
        const char * s;
    };

    const array<Puzzle, 12> puzzles = { {
        {
            "wikipedia_hard", 10, 9,
            "2        2\n"
            "      2   \n"
            " 2  7     \n"
            "          \n"
            "      3 3 \n"
            "  2    3  \n"
            "2  4      \n"
            "          \n"
            " 1    2 4 \n"
        },

        {
            "wikipedia_easy", 10, 10,
            "1   4  4 2\n"
            "          \n"
            " 1   2    \n"
            "  1   1  2\n"
            "1    3    \n"
            "  6      5\n"
            "          \n"
            "     1   2\n"
            "    2  2  \n"
            "          \n"
        },

        { // http://nikoli.com/en/puzzles/nurikabe/
            "nikoli_1", 10, 10,
            "       5 2\n"
            "3         \n"
            " 4  2     \n"
            "      3   \n"
            " 4   4    \n"
            "         3\n"
            "          \n"
            "          \n"
            " 3  3     \n"
            "  1  1 3 3\n"
        },

        {
            "nikoli_2", 10, 10,
            "6 2 3    3\n"
            "          \n"
            "         4\n"
            "          \n"
            "    2    2\n"
            "3    5    \n"
            "          \n"
            "3         \n"
            "          \n"
            "4    5 4 1\n"
        },

        {
            "nikoli_3", 10, 10,
            " 3    4   \n"
            "     6    \n"
            "       2  \n"
            "      3   \n"
            "        2 \n"
            " 4     3  \n"
            "         1\n"
            " 10      3 \n"
            "          \n"
            "  3      2\n"
        },

        {
            "nikoli_4", 18, 10,
            "  4            1 3\n"
            " 3    5   1 2     \n"
            "       5 3        \n"
            "            2 3   \n"
            "  4             3 \n"
            " 3             4  \n"
            "   1 1            \n"
            "        3 4       \n"
            "     1 1   5    5 \n"
            "4 4            3  \n"
        },

        {
            "nikoli_5", 18, 10,
            " 1 1    1     1   \n"
            "    5    2     1  \n"
            "        1     1   \n"
            "     5         1  \n"
            "1 1       4   1   \n"
            " 1     3     7    \n"
            "  3              6\n"
            "    4   2  4      \n"
            "      5         5 \n"
            " 1           5    \n"
        },

        {
            "nikoli_6", 18, 10,
            "                  \n"
            "1    12     3 12    \n"
            "                 2\n"
            "2    3     3    3 \n"
            "    1     1       \n"
            "3    1            \n"
            "   2  2 3 2       \n"
            "2           1     \n"
            "  3               \n"
            "1              12 1\n"
        },

        {
            "nikoli_7", 24, 14,
            "    5                   \n"
            "          2 6    7 3   4\n"
            "  1    5        3 5     \n"
            " 7   6                 1\n"
            "        4               \n"
            "   1      1   5      3  \n"
            "  2  3                  \n"
            "        3   3   2  7    \n"
            "                        \n"
            "6   1    5   5   1    5 \n"
            "      6        5     3  \n"
            "   4               4    \n"
            " 5          1           \n"
            "        3 4     5       \n"
        },

        {
            "nikoli_8", 24, 14,
            "    2 1           5 5   \n"
            "  4             12     1 \n"
            " 7      1               \n"
            "              1        3\n"
            "          7             \n"
            "6            5          \n"
            "           6           1\n"
            "9           15           \n"
            "          3            3\n"
            "             8          \n"
            "2        8              \n"
            "               4      3 \n"
            " 4     5             3  \n"
            "   8 3           2 4    \n"
        },

        {
            "nikoli_9", 36, 20,
            "2   2  1  1               1         \n"
            "   4    3        9      8      5    \n"
            "      1        7                   5\n"
            "4      1  1  4              2    1  \n"
            "      2  3         2         1 3    \n"
            "4   2           5    2              \n"
            "       1  1 17          3 4        4 \n"
            "                 9              21  2\n"
            "2       2                 4         \n"
            "  7  4            3   13             \n"
            "          1               6    1    \n"
            "  4      2    9  1                  \n"
            "     6               3          9   \n"
            "22                  1      8  1      \n"
            "   1   6   1   4                    \n"
            "    2     2     1      1       1   1\n"
            "                  4     2           \n"
            "   3 3   2   2       8      2     3 \n"
            "            1              1        \n"
            "                3       5       5   \n"
        },

        {
            "nikoli_10", 36, 20,
            "           4            2           \n"
            "3 4          2   7         8      2 \n"
            "    7      5   1   8 5   1  2  4   2\n"
            "6    4       3          2 2         \n"
            "           6                   4    \n"
            "    2             1  2           2  \n"
            "        1       4     4    4  1     \n"
            " 1                  3            4 4\n"
            "     2     4  4            4        \n"
            "       5  3                   2 4   \n"
            " 5 1              1    3   8   2    \n"
            "     1   2                          \n"
            "2            2 5           4     2 1\n"
            "                             2      \n"
            "1  2   4  7   18   1            1   1\n"
            "                     2   8 4        \n"
            "    3           18     1          4  \n"
            "                 4                4 \n"
            "      3 1   4      4    2    4   4  \n"
            "6      1  3                 4       \n"
        },
    } };

    try {
        for (const auto& puzzle : puzzles) {
            const auto start = steady_clock::now();

            Grid g(puzzle.w, puzzle.h, puzzle.s);

            while (g.solve() == Grid::KEEP_GOING) { }

            const auto finish = steady_clock::now();


            ofstream f(puzzle.name + string(".html"));

            g.write(f, start, finish);


            cout << puzzle.name << ": " << format_tim(start, finish) << ", ";

            const int k = g.known();
            const int cells = puzzle.w * puzzle.h;

            cout << k << "/" << cells << " (" << k * 100.0 / cells << "%) solved" << endl;
        }
    } catch (const exception& e) {
        cerr << "EXCEPTION CAUGHT! \"" << e.what() << "\"" << endl;
        return EXIT_FAILURE;
    } catch (...) {
        cerr << "UNKNOWN EXCEPTION CAUGHT!" << endl;
        return EXIT_FAILURE;
    }
}
