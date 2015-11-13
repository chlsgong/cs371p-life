#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "Life.h"

using namespace std;

Cell::Cell() {
	current_state = false;
	age = 0;
	symbol = '-';
}
Cell::Cell(bool initial_state, char s) {
	current_state = initial_state;
	age = 0;
	symbol = s;
}
void Cell::evolve(int index, const Life<Cell>& l) {
	//cout << boolalpha << current_state << endl; 
	next_state = l.inspectNeighbors(current_state, index);
	if(next_state) {
		++age;
		if(age >= 2)
			symbol = '*'; // ConwayCell evolve
		else {
			// FredkinCell evolve
			if(age >= 10)
				symbol = '+';
			else
				symbol = (char) age;
		}
	}
	else {
		if(age >= 2)
			symbol = '.';
		else
			symbol = '-';
	}
}


ConwayCell::ConwayCell() {
	current_state = false;
	symbol = '.';
}
ConwayCell::ConwayCell(bool initial_state, char s) {
	current_state = initial_state;
	symbol = s;
}
void ConwayCell::evolve(int index, const Life<ConwayCell>& l) {
	// cout << boolalpha << current_state << endl; 
	next_state = l.inspectNeighbors(current_state, index);
	if(next_state)
		symbol = '*';
	else
		symbol = '.';
}


FredkinCell::FredkinCell() {
	current_state = false;
	age = 0;
	symbol = '-';
}
FredkinCell::FredkinCell(bool initial_state, char s) {
	current_state = initial_state;
	age = 0;
	symbol = s;
}
void FredkinCell::evolve(int index, const Life<FredkinCell>& l) {
	// cout << boolalpha << current_state << endl; 
	next_state = l.inspectNeighbors(current_state, index);
	if(next_state) {
		++age;
		if(age >= 10)
			symbol = '+';
		else
			symbol = (char) age;
	}
	else
		symbol = '-';
}

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

		if(cell_type == "Cell") {
			Life<Cell> l(rows, columns, grid);
			l.runLife(evolutions);
		}
		else if(cell_type == "ConwayCell") {
			Life<ConwayCell> l(rows, columns, grid);
			l.runLife(evolutions);
		}
		else if(cell_type == "FredkinCell") {
			Life<FredkinCell> l(rows, columns, grid);
			l.runLife(evolutions);
		}

	}
}
