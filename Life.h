#ifndef DARWIN_H
#define DARWIN_H

#include <iostream>
#include <vector>
#include <iterator>

class ConwayCell;
class FredkinCell;

template<typename T>
class L_Iterator {
	private:
		T _v;

	public:
		L_Iterator(const T& v) {
			_v = v;
		}
		bool operator == (const L_Iterator<T>& rhs) const {
			return (_v == rhs._v);
		}
		bool operator != (const L_Iterator<T>& rhs) const {
			return !(*this == rhs);
		}
		const T& operator * () const {
			return _v;
		}
		L_Iterator<T> operator ++ () { // pre increment
			++_v;
			return *this;
		}
		L_Iterator<T> operator ++ (int) { // post increment
			L_Iterator<T> d = *this;
			++*this;
			return d;
		}
};

template<typename T>
class Life {
	private:
		int rows;
		int columns;
		std::vector<T> grid;
	public:
		Life(int r, int c, std::vector<char> g) {
			rows = r;
			columns = c;
			int size = r*c;
			for(int i = 0; i < size; i++) {
				if(g[i] == '.') { // dead conway cell
					T cell = new ConwayCell(false, '.');
					grid.push_back(cell);
				}
				else if(g[i] == '-') { // dead fredkin cell
					T cell = new FredkinCell(false, '-');
					grid.push_back(cell);
				}
				else if(g[i] == '*') { // live conway cell
					T cell = new ConwayCell(true, '*');
					grid.push_back(cell);
				}
				else { // live fredkin cell
					T cell = new FredkinCell(true, '0');
					grid.push_back(cell);
				}
			}
		}

		void runLife(int evolutions) {
			// call cell.evolve(i)
			for(int i = 0; i < evolutions; i++) {
				L_Iterator<int> b = this->begin();
				L_Iterator<int> e = this->end();
				while(b != e) {
					//std::cout << *b << std::endl;
					//std::cout << *e << std::endl;
					grid[*b].evolve(*b, *this);
					++b;
				}
			}
			for(int i = 0; i < rows*columns; i++) {
				char s = grid[i].symbol;
				std::cout << s << std::endl;
			}
		}

		bool inspectNeighbors(char state, int position) {
			// counts alive neighbor cells
			// return true if alive, false if dead
			return true;
		}

		L_Iterator<int> begin() {
			L_Iterator<int> b(0);
			return b;
		}
		L_Iterator<int> end() {
			int end = rows * columns;
			L_Iterator<int> e(end);
			return e;
		}
};

class AbstractCell {
	protected:
		bool current_state; // true = alive, false = dead
		bool next_state;
		char symbol;

	public:
		virtual void evolve(int) = 0;
};

class Cell: public AbstractCell {
	protected:
		int age;

	public:
		Cell();
		Cell(bool, char);
		void evolve(int, const Life<Cell>&);
};

class ConwayCell: public Cell {
	public:
		ConwayCell();
		ConwayCell(bool, char);
		void evolve(int, const Life<ConwayCell>&);
};

class FredkinCell: public Cell {
	public:
		FredkinCell();
		FredkinCell(bool, char);
		void evolve(int, const Life<FredkinCell>&);
};

void enact_life(std::istream& r);

#endif // DARWIN_H
