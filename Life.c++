#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cstring>

#include "Life.h"

using namespace std;

// class Cell
Cell::Cell() {
	FredkinCell fc;
	ac_ptr = fc.clone();
}
Cell::Cell(const AbstractCell* ac): ac_ptr(ac->clone()) {} // AbstractCell constructor
Cell::Cell(bool initial_state, char s) {
	if(s == '.')
		ac_ptr = new ConwayCell(initial_state, s);
	else if(s == '-')
		ac_ptr = new FredkinCell(initial_state, s);
	else if(s == '*')
		ac_ptr = new ConwayCell(initial_state, s);
	else
		ac_ptr = new FredkinCell(initial_state, s);
}
void Cell::operator = (const Cell& c) {
	ac_ptr = c.ac_ptr->clone();
}
void Cell::evolve(int index, Life<Cell>& l) {
	ac_ptr->evolve(index, l);
}
bool Cell::canMutate() {
	return ac_ptr->canMutate();
}
int Cell::changeState() {
	return ac_ptr->changeState();
}
int Cell::isAlive(int count) {
	return ac_ptr->isAlive(count);
}
ostream& operator << (ostream& os, const Cell& c) {
	os << c.ac_ptr->symbol;
	return os;
}

// class ConwayCell
ConwayCell::ConwayCell() {
	current_state = false;
	symbol = '.';
}
ConwayCell::ConwayCell(AbstractCell*) {}
ConwayCell::ConwayCell(bool initial_state, char s) {
	current_state = initial_state;
	symbol = s;
}
ConwayCell* ConwayCell::clone() const {
	return new ConwayCell(*this);
}
void ConwayCell::evolve(int index, Life<ConwayCell>& l) {
	next_state = l.inspectNeighbors(index, symbol);
	if(next_state)
		symbol = '*';
	else
		symbol = '.';
}
void ConwayCell::evolve(int index, Life<Cell>& l) {
	next_state = l.inspectNeighbors(index, symbol);
	if(next_state)
		symbol = '*';
	else
		symbol = '.';
}
ostream& operator << (ostream& os, const ConwayCell& cc) {
	os << cc.symbol;
	return os;
}

// class FredkinCell
FredkinCell::FredkinCell() {
	current_state = false;
	age = 0;
	symbol = '-';
}
FredkinCell::FredkinCell(AbstractCell*) {}
FredkinCell::FredkinCell(bool initial_state, char s) {
	current_state = initial_state;
	age = 0;
	symbol = s;
}
FredkinCell* FredkinCell::clone() const {
	return new FredkinCell(*this);
}
void FredkinCell::evolve(int index, Life<FredkinCell>& l) {
	next_state = l.inspectNeighbors(index, symbol);
	if(next_state) {
		if(current_state == next_state)
			++age;
		if(age >= 10)
			symbol = '+';
		else {
			string str_tmp = to_string(age);
			symbol = str_tmp[0];
		}
	}
	else
		symbol = '-';
}
void FredkinCell::evolve(int index, Life<Cell>& l) {
	next_state = l.inspectNeighbors(index, symbol);
	if(next_state) {
		if(current_state == next_state)
			++age;
		if(age >= 10)
			symbol = '+';
		else {
			string str_tmp = to_string(age);
			symbol = str_tmp[0];
		}
	}
	else
		symbol = '-';
}
ostream& operator << (ostream& os, const FredkinCell& fc) {
	os << fc.symbol;
	return os;
}


void enact_life(istream& r, ostream& w) {
	string s;
	string cell_type;
	int rows;
	int columns;
	int evolutions;
	int frequency;
	char cell;
	vector<char> grid;

	int flag = 0;
	istringstream sin;
	while(getline(r, cell_type)) { // type of cell
		if(flag == 1)
			w << endl;
		flag = 1;
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
			for(int j = 0; j < columns; j++) {
				sin >> cell; // each cell in grid
				sin.clear();
				grid.push_back(cell);
			}
		}

		getline(r, s); // blank line

		if(cell_type == "Cell") {
			Life<Cell> l(rows, columns, grid);
			w << "*** Life<Cell> " << rows << "x" << columns << " ***" << endl;
			for(int i = 0; i <= evolutions; i++) {
				if(i % frequency == 0) {
					w << endl;
					w << "Generation = " << i << ", " << l;
				}
				l.runLife();
			}
		}
		else if(cell_type == "ConwayCell") {
			Life<ConwayCell> l(rows, columns, grid);
			w << "*** Life<ConwayCell> " << rows << "x" << columns << " ***" << endl;
			for(int i = 0; i <= evolutions; i++) {
				if(i % frequency == 0) {
					w << endl;
					w << "Generation = " << i << ", " << l;
				}
				l.runLife();
			}		
		}
		else if(cell_type == "FredkinCell") {
			Life<FredkinCell> l(rows, columns, grid);
			w << "*** Life<FredkinCell> " << rows << "x" << columns << " ***" << endl;
			for(int i = 0; i <= evolutions; i++) {
				if(i % frequency == 0) {
					w << endl;
					w << "Generation = " << i << ", " << l;
				}
				l.runLife();
			}
		}

		grid.clear(); // reset vector
	}
}
