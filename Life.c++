#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "Life.h"

using namespace std;

// class Cell
Cell::~Cell() {
	delete ac_ptr;
}
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
void Cell::changeState() {
	ac_ptr->changeState();
}
int Cell::isAlive(int count) {
	return ac_ptr->isAlive(count);
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
	// cout << boolalpha << current_state << endl; 
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
	// cout << boolalpha << current_state << endl; 
	next_state = l.inspectNeighbors(index, symbol);
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
void FredkinCell::evolve(int index, Life<Cell>& l) {
	next_state = l.inspectNeighbors(index, symbol);
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
			cout << "*** Life<Cell> " << rows << "x" << columns << " ***" << endl;
			cout << endl;
			for(int i = 0; i < evolutions; i++) {
				l.runLife();
				// generation, population
				if(i % frequency == 0)
					cout << l << endl;
			}
		}
		else if(cell_type == "ConwayCell") {
			Life<ConwayCell> l(rows, columns, grid);
			cout << "*** Life<ConwayCell> " << rows << "x" << columns << " ***" << endl;
			cout << endl;
			for(int i = 0; i < evolutions; i++) {
				l.runLife();
				// generation, population
				if(i % frequency == 0)
					cout << l << endl;
			}		
		}
		else if(cell_type == "FredkinCell") {
			Life<FredkinCell> l(rows, columns, grid);
			cout << "*** Life<FredkinCell> " << rows << "x" << columns << " ***" << endl;
			cout << endl;
			for(int i = 0; i < evolutions; i++) {
				l.runLife();
				// generation, population
				if(i % frequency == 0)
					cout << l << endl;
			}
		}
		cout << endl;
	}
}
