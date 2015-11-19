#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

int main() {
	srand(time(NULL));
	int rows;
	int columns;
	int state;
	int cell_type;
	int cell_cell_type;
	int evolutions;
	int frequency;

	for(int k = 0; k < 15; k++) {
		cell_type = rand() % 3;
		if(cell_type == 0)
			cout << "Cell" << endl;
		else if(cell_type == 1)
			cout << "ConwayCell" << endl;
		else
			cout << "FredkinCell" << endl;
		rows = rand() % 100 + 1;
		cout << rows << endl;
		columns = rand() % 100 + 1;
		cout << columns << endl;
		evolutions = rand() % 100 + 1;
		cout << evolutions << endl;
		frequency = rand() % 10 + 1;
		cout << frequency << endl;
		for(int i = 0; i < rows; i++) {
			for(int j = 0; j < columns; j++) {
				state = rand() % 2;
				if(cell_type == 1) {
					if(state == 0)
						cout << "*";
					else
						cout << ".";
				}
				else if(cell_type == 2) {
					if(state == 1)
						cout << "0";
					else
						cout << "-";
				}
				else {
					cell_cell_type = rand() % 2;
					if(cell_cell_type == 0) {
						if(state == 0)
							cout << "0";
						else
							cout << "-";
					}
					else {
						if(state == 0)
							cout << "*";
						else
							cout << ".";
					}
				}
			}
			cout << endl;
		}
		cout << endl;
	}

	return 0;
}

// g++ -pedantic -std=c++11 -Wall LifeTestMaker.c++ -o LifeTestMaker
