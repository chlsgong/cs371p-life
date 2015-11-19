#include <iostream>
#include <sstream>
#include <string>
#include "Life.h"
#include "gtest/gtest.h"

using namespace std;

// g++ -fprofile-arcs -ftest-coverage -pedantic -std=c++11 -Wall Life.c++ TestLife.c++ -o TestLife -lgtest -lgtest_main -lpthread


//AbstractCell

// TEST(AbstractCellFixture, abstract_cell_destructor) {
// 	AbstractCell *c = new ConwayCell();
// 	delete(c);
// 	ASSERT_EQ(nullptr, c);  //review this

// }

//add other ac destructor  text

TEST(AbstractCellFixture, abstract_cell_canMutate) {
	AbstractCell *c = new ConwayCell();
	ASSERT_FALSE(c->canMutate());
}

TEST(AbstractCellFixture, abstract_cell_changeState) {
	AbstractCell *c = new ConwayCell();
	ASSERT_EQ(0, c->changeState());
}

TEST(AbstractCellFixture, abstract_cell_isAlive) {
	AbstractCell *c = new ConwayCell();
	ASSERT_EQ(5, c->isAlive(5)); //current state is false by default
}

TEST(ConwayCellFixture, conway_cell_default_constructor) {
	ConwayCell c;
	ASSERT_EQ(0, c.changeState());
	ostringstream o;
	o << c;
	ASSERT_EQ(".", o.str());
}

TEST(ConwayCellFixture, conway_cell_custom_constructor) {
	ConwayCell c(true, '*');
	ASSERT_EQ(2, c.changeState());
	ostringstream o;
	o << c;
	ASSERT_EQ("*", o.str());
}

TEST(ConwayCellFixture, conway_cell_clone) {
	AbstractCell *c = new ConwayCell();
	AbstractCell *p = c->clone();
	ASSERT_NE(c, p);
	ASSERT_EQ(c->changeState(), p->changeState());
}

// TEST(ConwayCellFixture, conway_cell_evolve_Life_Cell) {
// 	Life<Cell> l(10, 10, );
// 	Cell c = l.at(15);
// 	ostringstream o;
// 	o << c;
// 	ASSERT_EQ(".", o.str());
// }

TEST(ConwayCellFixture, conway_cell_evolve_Life_ConwayCell) {
	Life<ConwayCell> l;
	ConwayCell c = l.at(25);
	ostringstream o;
	o << c;
	ASSERT_EQ(".", o.str());
}

//TEST ALL THE FRIEND FUNCTION OPERATOR <<