#ifndef DARWIN_H
#define DARWIN_H

#include <iostream>
#include <vector>
#include <iterator>
#include <type_traits>

template<typename T> class Life;
class Cell;

class AbstractCell {
	protected:
		bool current_state; // true = alive, false = dead
		bool next_state;
		char symbol;
		int age;

	public:
		virtual ~AbstractCell() {}
		virtual AbstractCell* clone() const = 0;
		virtual void evolve(int, Life<Cell>&) = 0;
		virtual bool canMutate() {
			if(age == 2 && current_state)
				return true;
			return false;
		}
		virtual int changeState() {
			int pop_flag; // 0 = pop doesnt change, 1 = pop increases, 2 = pop decreases
			if(current_state != next_state && next_state) // if state did change and next state is alive
				pop_flag = 1;
			else if(current_state != next_state && !next_state)
				pop_flag = 2;
			else
				pop_flag = 0;
			current_state = next_state;
			return pop_flag;
		}
		virtual int isAlive(int count) {
			if(current_state)
				return ++count;
			return count;
		}
};

class ConwayCell: public AbstractCell {
	public:
		ConwayCell();
		ConwayCell(AbstractCell*);
		ConwayCell(bool, char);
		ConwayCell* clone() const;
		void evolve(int, Life<ConwayCell>&);
		void evolve(int, Life<Cell>&);
		friend std::ostream& operator << (std::ostream&, const ConwayCell&);
};

class FredkinCell: public AbstractCell {
	public:
		FredkinCell();
		FredkinCell(AbstractCell*);
		FredkinCell(bool, char);
		FredkinCell* clone() const;
		void evolve(int, Life<FredkinCell>&);
		void evolve(int, Life<Cell>&);
		friend std::ostream& operator << (std::ostream& os, const FredkinCell& fc);
};

class Cell {
	AbstractCell* ac_ptr; // holds AbstractCell pointer

	public:
		~Cell();
		Cell();
		Cell(const AbstractCell*); // AbstractCell constructor
		Cell(bool, char);
		void operator = (const Cell&); // Cell assignment
		void evolve(int, Life<Cell>&);
		bool canMutate();
		int changeState();
		int isAlive(int);
		friend std::ostream& operator << (std::ostream&, const Cell&);
};

template<typename T>
class L_Iterator {
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
	int rows;
	int columns;
	int size;
	int population = 0;
	std::vector<T> grid;

	public:
		Life() {
			rows = 10;
			columns = 10;
			size = rows * columns;
			if(std::is_same<Cell, T>::value) { // if Cell 
				for(int i = 0; i < size; i++) {
					T cell = new FredkinCell(true, '0');
					grid.push_back(cell);
				}
				population = 100;
			}
			else if(std::is_same<ConwayCell, T>::value) {
				for(int i = 0; i < size; i++) {
					T cell = new ConwayCell(false, '-');
					grid.push_back(cell);
				}
				population = 0;
			}
			else {
				for(int i = 0; i < size; i++) {
					T cell = new FredkinCell(false, '-');
					grid.push_back(cell);
				}
				population = 0;
			}
		}
		Life(int r, int c, std::vector<char> g) { // custom constructor
			rows = r;
			columns = c;
			size = r*c;
			if(std::is_same<Cell, T>::value) { // if Cell
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
						++population;
					}
					else { // live fredkin cell
						T cell = new FredkinCell(true, '0');
						grid.push_back(cell);
						++population;
					}
				}
			}
			else {
				for(int i = 0; i < size; i++) {
					if(g[i] == '.' || g[i] == '-') {
						T cell(false, g[i]);
						grid.push_back(cell);
					}
					else {
						T cell(true, g[i]);
						grid.push_back(cell);
						++population;
					}
				}
			}
		}
		void runLife() {
			L_Iterator<int> b = this->begin();
			L_Iterator<int> e = this->end();
			while(b != e) {
				grid[*b].evolve(*b, *this);
				++b;
			}
			
			b = this->begin(); // reset b
			int pop_change_flag;
			if(std::is_same<Cell, T>::value) {
				while(b != e) {
					pop_change_flag = grid[*b].changeState();
					if(pop_change_flag == 1)
						++population;
					else if(pop_change_flag == 2)
						--population;

					if(grid[*b].canMutate()) { // mutate cells if needed
						T temp = new ConwayCell(true, '*');
						grid[*b].~T();
						grid[*b] = temp;
					}
					++b;
				}
			}
			else {
				while(b != e) {
					pop_change_flag = grid[*b].changeState();
					if(pop_change_flag == 1)
						++population;
					else if(pop_change_flag == 2)
						--population;
					++b;
				}
			};
		}
		bool inspectNeighbors(int i, char symbol) {
			// counts alive neighbor cells
			// return true if alive, false if dead
			int count = 0;
			if(symbol == '.' || symbol == '*') { // conway cell
				// top left corner
				if(i-columns-1 > 0 && i%columns != 0)
					count = grid[i-columns-1].isAlive(count);
				// top edge
				if(i-columns > 0)
					count = grid[i-columns].isAlive(count);
				// top right corner
				if(i-columns+1 > 0 && (i+1)%columns != 0)
					count = grid[i-columns+1].isAlive(count);
				// left edge
				if(i-1 > 0 && i%columns != 0)
					count = grid[i-1].isAlive(count);
				// right edge
				if(i+1 < size && (i+1)%columns != 0)
					count = grid[i+1].isAlive(count);
				// bottom left corner
				if(i+columns-1 < size && i%columns != 0)
					count = grid[i+columns-1].isAlive(count);
				// bottom edge
				if(i+columns < size)
					count = grid[i+columns].isAlive(count);
				// bottom right corner
				if(i+columns+1 < size && (i+1)%columns != 0)
					count = grid[i+columns+1].isAlive(count);
				
				if(symbol == '.' && count == 3)
					return true;
				else if(symbol == '.' && count != 3)
					return false;
				else if(symbol == '*' && (count < 2 || count > 3))
					return false;
				else
					return true;
			}
			else { // fredkin cell
				// top edge
				if(i-columns > 0)
					count = grid[i-columns].isAlive(count);
				// left edge
				if(i-1 > 0 && i%columns != 0)
					count = grid[i-1].isAlive(count);
				// right edge
				if(i+1 < size && (i+1)%columns != 0)
					count = grid[i+1].isAlive(count);
				// bottom edge
				if(i+columns < size)
					count = grid[i+columns].isAlive(count);
				
				if(symbol == '-' && count % 2 != 0) // if odd then alive
					return true;
				else if(symbol == '-' && count % 2 == 0)
					return false;
				else if(count % 2 == 0)
					return false;
				else
					return true;
			}
		}
		friend std::ostream& operator << (std::ostream& os, const Life<T>& l) {
			os << "Population = " << l.population << ".\n";
			for(int i = 0; i < l.rows; i++) {
				for(int j = 0; j < l.columns; j++)
					os << l.at(i*l.columns+j);
				os << "\n";
			}
			return os;
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
		T at(int index) const {
			return grid[index];
		}
};

void enact_life(std::istream& r);

#endif // DARWIN_H
