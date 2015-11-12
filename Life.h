#ifndef DARWIN_H
#define DARWIN_H

#include <iostream>

class AbstractCell {
	protected:
		bool alive;

	public:
		virtual void evolve(int index) = 0;
};

class Cell: public AbstractCell {
	void evolve(int index);
};

class ConwayCell: public Cell {
	void evolve(int index);
};

class FredkinCell: public Cell {
	void evolve(int index);
};

template<typename T>
class Life {
	private:
		int rows;
		int columns;
		vector<T> grid;
	public:
		Life(int r, int c, vector<char> g) {
			rows = r;
			columns = c;
			int size = r*c;
			for(int i = 0; i < size; i++) {
				if(g[i] == '.') { // dead conway cell
					T cell(false) = new ConwayCell;
					grid.push_back(cell);
				}
				else if(g[i] == '-') { // dead fredkin cell
					T cell(false) = new FredkinCell;
					grid.push_back(cell);
				}
				else if(g[i] == '*') { // live conway cell
					T cell(true) = new ConwayCell;
					grid.push_back(cell);
				}
				else { // live fredkin cell
					T cell(true) = new FredkinCell;
					grid.push_back(cell);
				}
			}
		}

		void runLife(int evolutions) {
			// call cell.evolve(i)
		}

		bool inspectNeighbors(char state, int position) {
			// counts alive neighbor cells
			// return true if change is needed, false if not
		}
};

void enact_life(std::istream& r);

#endif // DARWIN_H
