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



TEST(AbstractCellFixture, abstract_cell_canMutate_1) {
	AbstractCell *c = new ConwayCell();
	ASSERT_FALSE(c->canMutate());
}

TEST(AbstractCellFixture, abstract_cell_canMutate_2) {
	AbstractCell *c = new FredkinCell(true, '0');
	Life<Cell> l;

	ASSERT_FALSE(c->canMutate());
}

TEST(AbstractCellFixture, abstract_cell_canMutate_3) {
	AbstractCell *c = new FredkinCell(true, '0');
	Life<Cell> l;

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

// ----------------
// Life Constructor 
// ----------------

TEST(LifeFixture, Life_default_constructor_1) {
	ASSERT_NO_THROW(Life<Cell> l());
}

TEST(LifeFixture, Life_default_constructor_2) {
	ASSERT_NO_THROW(Life<ConwayCell> l());
}

TEST(LifeFixture, Life_default_constructor_3) {
	ASSERT_NO_THROW(Life<FredkinCell> l());
}



// TEST(Life, Life_custom_constructor_1) {
// 	ASSERT_NO_THROW(Life<Cell> l());
// }

// TEST(Life, Life_custom_constructor_2) {
// 	ASSERT_NO_THROW(Life<ConwayCell> l());
// }

// TEST(Life, Life_custom_constructor_3) {
// 	ASSERT_NO_THROW(Life<FredkinCell> l());
// }

	


TEST(LifeFixture, Life_runLife_1) {

}

TEST(LifeFixture, Life_inspectNeighbors_1) {

}

TEST(LifeFixture, Life_at_1) {
	vector<char> v(12);
	for (int i = 0; i < 12; ++i) {
		v.push_back('.');
	}
	Life<ConwayCell> l(4,4,v);
	ASSERT_EQ(l.at(9).isAlive(0), 1);
}

TEST(LifeFixture, Life_at_2) {
	vector<char> v(12);
	for (int i = 0; i < 12; ++i) {
		v.push_back('-');
	}
	Life<FredkinCell> l(4,4,v);
	ASSERT_EQ(l.at(9).isAlive(0), 1);
}

TEST(LifeFixture, Life_at_3) {
	vector<char> v(12);
	for (int i = 0; i < 12; ++i) {
		v.push_back('-');
	}
	Life<Cell> l(4,4,v);
	ASSERT_EQ(l.at(9).isAlive(0), 1);
}

// TEST(LifeFixture, Life_begin_1) {
	
// 	Life<ConwayCell> l;
// 	auto b = l.begin();
// 	ASSERT_EQ(0, (*b).isAlive(0));
// }

TEST(LifeFixture, Life_end_1) {

}


TEST(Functions, enactLife_1) {

}







//TEST ALL THE FRIEND FUNCTION OPERATOR <<

TEST(OperatorFixture, output_operator_Cell_1) {
	Cell c;
	ostringstream out;
	out << c;
	ASSERT_EQ(out.str(), "-");
}

TEST(OperatorFixture, output_operator_Cell_2) {
	Cell c(true, '0');
	ostringstream out;
	out << c;
	ASSERT_EQ(out.str(), "0");
}

TEST(OperatorFixture, output_operator_Cell_3) {
	Cell c(false, '-');
	ostringstream out;
	out << c;
	ASSERT_EQ(out.str(), "-");
}

TEST(OperatorFixture, output_operator_ConwayCell_1) {
	ConwayCell c;
	ostringstream out;
	out << c;
	ASSERT_EQ(out.str(), ".");
}

TEST(OperatorFixture, output_operator_ConwayCell_2) {
	ConwayCell c(true, '*');
	ostringstream out;
	out << c;
	ASSERT_EQ(out.str(), "*");
}

TEST(OperatorFixture, output_operator_ConwayCell_3) {
	ConwayCell c(false, '.');
	ostringstream out;
	out << c;
	ASSERT_EQ(out.str(), ".");
}

TEST(OperatorFixture, output_operator_FredkinCell_1) {
	FredkinCell c;
	ostringstream out;
	out << c;
	ASSERT_EQ(out.str(), "-");
}

TEST(OperatorFixture, output_operator_FredkinCell_2) {
	FredkinCell c(true, '0');
	ostringstream out;
	out << c;
	ASSERT_EQ(out.str(), "0");
}

TEST(OperatorFixture, output_operator_FredkinCell_3) {
	FredkinCell c(false, '-');
	ostringstream out;
	out << c;
	ASSERT_EQ(out.str(), "-");
}
// TEST(OperatorFixture, output_operator_Life_1) {
// 	string s = "Population = 12.\n\0\\0\\0\\0\n\\0\\0\\0\\0\n\\0\\0\\0\\0\n";
// 	vector<char> v(12);
// 	for (int i = 0; i < 12; ++i) {
// 		v.push_back('0');
// 	}
// 	Life<ConwayCell> l(3,4,v);

// 	ostringstream out;
// 	out << l;
// 	ASSERT_EQ(s, out.str());
// }


// g++ -fprofile-arcs -ftest-coverage -pedantic -std=c++11 -Wall Life.c++ TestLife.c++ -o TestLife -lgtest -lgtest_main -lpthread
