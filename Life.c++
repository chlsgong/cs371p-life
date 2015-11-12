#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

void enact_life(istream& r) {
	string s;
	string cell_type;
	int rows;
	int columns;
	int evolutions;
	int frequency;
	char cell;
	vector<char> grid;

	istringstream sin;
	while(getline(r, cell_type)) { // type of cell
		getline(r, s);
		sin.str(s);
		sin >> rows; // number of rows
		sin.clear();

		getline(r, s);
		sin.str(s);
		sin >> columns; // number of columns
		sin.clear();

		getline(r, s);
		sin.str(s);
		sin >> evolutions; // number of evolutions
		sin.clear();

		getline(r, s);
		sin.str(s);
		sin >> frequency; // print frequency
		sin.clear();

		for(int i = 0; i < rows; i ++) {
			getline(r, s);
			sin.str(s);
			for(int i = 0; i < columns; i++) {
				sin >> cell; // each cell in grid
				sin.clear();
				grid.push_back(cell);
			}
		}

		getline(r, s); // blank line

		// ... code

	}
}
