#include <iostream>
#include <sstream>
#include <string>
#include "Life.h"
#include "gtest/gtest.h"

using namespace std;

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

TEST(ConwayCellFixture, conway_cell_evolve_Life_Cell) {
	Life<Cell> l;
	Cell c = l.at(15);
	c.evolve(15, l);
	ASSERT_EQ(1, c.isAlive(0));
	// ostringstream o;
	// o << c;
	// ASSERT_EQ(".", o.str());
}

// TEST(ConwayCellFixture, conway_cell_evolve_Life_ConwayCell) {
// 	Life<ConwayCell> l;
// 	ConwayCell c = l.at(25);
// 	c.evolve(25, l);
// 	ASSERT_EQ(1, c.isAlive(1));
// 	// ostringstream o;
// 	// o << c;
// 	// ASSERT_EQ(".", o.str());
// }

TEST(FredkinCellFixture, fredkin_cell_default_constructor) {
	FredkinCell c;
	ASSERT_EQ(0, c.changeState());
	ostringstream o;
	o << c;
	ASSERT_EQ("-", o.str());
}

TEST(FredkinCellFixture, fredkin_cell_custom_constructor) {
	FredkinCell c(true, '0');
	ASSERT_EQ(2, c.changeState());
	ostringstream o;
	o << c;
	ASSERT_EQ("0", o.str());
}

//REST OF FREDKIN HERE

TEST(CellFixture, cell_default_constructor) {
	FredkinCell fc;
	Cell c;
	ASSERT_EQ(fc.isAlive(0), c.isAlive(0));
}

TEST(CellFixture, cell_abstractCell_constructor) {
	FredkinCell fc;
	Cell c = new FredkinCell();
	ASSERT_EQ(fc.isAlive(0), c.isAlive(0));
}

TEST(CellFixture, cell_custom_constructor) {
	FredkinCell fc;
	Cell c(false, '-');
	ASSERT_EQ(fc.isAlive(0), c.isAlive(0));
}

TEST(CellFixture, cell_assignment_operator) {
	Cell c = new FredkinCell();
	Cell p = c;
	ASSERT_EQ(c.isAlive(0), p.isAlive(0));
}

TEST(CellFixture, cell_evolve) {
	
	Life<Cell> l;
	Cell c = l.at(27);
	c.evolve(27, l);
	ASSERT_EQ(1, c.isAlive(0));
}

TEST(CellFixture, cell_canMutate) {
	Life<Cell> l;
	Cell c = l.at(27);
	ASSERT_FALSE(c.canMutate());
}

TEST(CellFixture, cell_changeState) {
	Cell c;
	ASSERT_EQ(0, c.changeState());
}

TEST(CellFixture, cell_isAlive) {
	Cell c;
	ASSERT_EQ(0, c.isAlive(0));
}



// L_Iterator constructor

TEST(L_IteratorFixture, constructor_1) {
	L_Iterator<int> x(0);
	ASSERT_EQ(*x, 0);
}
TEST(L_IteratorFixture, constructor_2) {
	L_Iterator<int> x(999999);
	ASSERT_EQ(*x, 999999);
}
TEST(L_IteratorFixture, constructor_3) {
	L_Iterator<double> x(0.5);
	ASSERT_EQ(*x, 0.5);
}

// == operator

TEST(L_IteratorFixture, equal_operator_1) {
	L_Iterator<int> x(0);
	L_Iterator<int> y(0);
	ASSERT_TRUE(x == y); 
}
TEST(L_IteratorFixture, equal_operator_2) {
	L_Iterator<int> x(0);
	L_Iterator<int> y(1);
	ASSERT_FALSE(x == y); 
}
TEST(L_IteratorFixture, equal_operator_3) {
	L_Iterator<double> x(0.5);
	L_Iterator<double> y(0.5);
	ASSERT_TRUE(x == y); 
}
TEST(L_IteratorFixture, equal_operator_4) {
	L_Iterator<double> x(0.5);
	L_Iterator<double> y(1.5);
	ASSERT_FALSE(x == y); 
}

// != operator

TEST(L_IteratorFixture, not_equal_operator_1) {
	L_Iterator<int> x(0);
	L_Iterator<int> y(1);
	ASSERT_TRUE(x != y); 
}
TEST(L_IteratorFixture, not_equal_operator_2) {
	L_Iterator<int> x(0);
	L_Iterator<int> y(0);
	ASSERT_FALSE(x != y); 
}
TEST(L_IteratorFixture, not_equal_operator_3) {
	L_Iterator<double> x(0.5);
	L_Iterator<double> y(1.5);
	ASSERT_TRUE(x != y);
}
TEST(L_IteratorFixture, not_equal_operator_4) {
	L_Iterator<double> x(0.5);
	L_Iterator<double> y(0.5);
	ASSERT_FALSE(x != y);
}

// * operator

TEST(L_IteratorFixture, dereference_operator_1) {
	L_Iterator<int> x(0);
	int i = *x + 1;
	ASSERT_EQ(i, 1);
}
TEST(L_IteratorFixture, dereference_operator_2) {
	L_Iterator<int> x(436375);
	ASSERT_EQ(x, 436375);
}

// pre-increment operator

TEST(L_IteratorFixture, pre_increment) {
	L_Iterator<int> x(0);
	++x;
	ASSERT_EQ(x, 1);
}

// post increment operator

TEST(L_IteratorFixture, post_increment) {
	L_Iterator<int> x(3);
	x++;
	ASSERT_EQ(x, 4);
}




//TEST ALL THE FRIEND FUNCTION OPERATOR <<

// g++ -fprofile-arcs -ftest-coverage -pedantic -std=c++11 -Wall Life.c++ TestLife.c++ -o TestLife -lgtest -lgtest_main -lpthread
