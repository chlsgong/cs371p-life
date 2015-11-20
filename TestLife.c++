#include <iostream>
#include <sstream>
#include <string>
#include "Life.h"
#include "gtest/gtest.h"

using namespace std;

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

TEST(AbstractCellFixture, abstract_cell_changeState_1) {
	AbstractCell *c = new ConwayCell();
	ASSERT_EQ(0, c->changeState());
}

TEST(AbstractCellFixture, abstract_cell_changeState_2) {
	AbstractCell *c = new ConwayCell(true, '*');
	ASSERT_EQ(2, c->changeState());
}

TEST(AbstractCellFixture, abstract_cell_changeState_3) {
	AbstractCell *c = new ConwayCell(false, '.');
	ASSERT_EQ(0, c->changeState());
}

TEST(AbstractCellFixture, abstract_cell_isAlive_1) {
	AbstractCell *c = new ConwayCell();
	ASSERT_EQ(5, c->isAlive(5)); //current state is false by default
}

TEST(AbstractCellFixture, abstract_cell_isAlive_2) {
	AbstractCell *c = new ConwayCell(true, '*');
	ASSERT_EQ(6, c->isAlive(5)); //current state is false by default
}

TEST(AbstractCellFixture, abstract_cell_isAlive_3) {
	AbstractCell *c = new ConwayCell(false, '.');
	ASSERT_EQ(5, c->isAlive(5)); //current state is false by default
}

TEST(ConwayCellFixture, conway_cell_default_constructor_1) {
	ConwayCell c;
	ASSERT_EQ(0, c.changeState());
	ostringstream o;
	o << c;
	ASSERT_EQ(".", o.str());
}

TEST(ConwayCellFixture, conway_cell_default_constructor_2) {
	ConwayCell c;
	ASSERT_EQ(0, c.isAlive(0)); 
}

TEST(ConwayCellFixture, conway_cell_default_constructor_3) {
	ConwayCell c;
	ASSERT_EQ(1, c.isAlive(1));;

}

TEST(ConwayCellFixture, conway_cell_custom_constructor_1) {
	ConwayCell c(true, '*');
	ASSERT_EQ(2, c.changeState());
	ostringstream o;
	o << c;
	ASSERT_EQ("*", o.str());
}

TEST(ConwayCellFixture, conway_cell_custom_constructor_2) {
	ConwayCell c(false, '.');
	ASSERT_EQ(0, c.changeState());
	ostringstream o;
	o << c;
	ASSERT_EQ(".", o.str());
}

TEST(ConwayCellFixture, conway_cell_custom_constructor_3) {
	ConwayCell c(false, '+');
	ASSERT_EQ(0, c.changeState());
	ostringstream o;
	o << c;
	ASSERT_EQ("+", o.str());
}

TEST(ConwayCellFixture, conway_cell_clone_1) {
	AbstractCell *c = new ConwayCell();
	AbstractCell *p = c->clone();
	ASSERT_NE(c, p);
	ASSERT_EQ(c->changeState(), p->changeState());
}

TEST(ConwayCellFixture, conway_cell_clone_2) {
	AbstractCell *c = new ConwayCell(false, '.');
	AbstractCell *p = c->clone();
	ASSERT_NE(c, p);
	ASSERT_EQ(c->changeState(), p->changeState());
}

TEST(ConwayCellFixture, conway_cell_clone_3) {
	AbstractCell *c = new ConwayCell(true, '*');
	AbstractCell *p = c->clone();
	ASSERT_NE(c, p);
	ASSERT_EQ(c->changeState(), p->changeState());
}

TEST(ConwayCellFixture, conway_cell_evolve_Life_Cell_1) {
	Life<Cell> l;
	Cell c = l.at(15);
	c.evolve(15, l);
	ASSERT_EQ(1, c.isAlive(0));
}

TEST(ConwayCellFixture, conway_cell_evolve_Life_Cell_2) {
	Life<Cell> l;
	Cell c = l.at(20);
	c.evolve(20, l);
	ASSERT_EQ(1, c.isAlive(0));
}

TEST(ConwayCellFixture, conway_cell_evolve_Life_Cell_3) {
	Life<Cell> l;
	Cell c = l.at(15);
	c.evolve(15, l);
	ASSERT_EQ(1, c.isAlive(0));
}

TEST(ConwayCellFixture, conway_cell_evolve_Life_ConwayCell_1) {
	Life<ConwayCell> l;
	ConwayCell c = l.at(0);
	c.evolve(0, l);
	ASSERT_EQ(0, c.isAlive(0));
}

TEST(ConwayCellFixture, conway_cell_evolve_Life_ConwayCell_2) {
	Life<ConwayCell> l;
	ConwayCell c = l.at(20);
	c.evolve(20, l);
	ASSERT_EQ(0, c.isAlive(0));
}

TEST(ConwayCellFixture, conway_cell_evolve_Life_ConwayCell_3) {
	Life<ConwayCell> l;
	ConwayCell c = l.at(15);
	c.evolve(15, l);
	ASSERT_EQ(0, c.isAlive(0));
}

TEST(FredkinCellFixture, fredkin_cell_default_constructor_1) {
	FredkinCell c;
	ASSERT_EQ(0, c.changeState());
	ostringstream o;
	o << c;
	ASSERT_EQ("-", o.str());
}

TEST(FredkinCellFixture, fredkin_cell_default_constructor_2) {
	FredkinCell c;
    ASSERT_EQ(0, c.isAlive(0));
}

TEST(FredkinCellFixture, fredkin_cell_default_constructor_3) {
	FredkinCell c;
    ASSERT_EQ(1, c.isAlive(1));
}

TEST(FredkinCellFixture, fredkin_cell_custom_constructor_1) {
	FredkinCell c(true, '0');
	ASSERT_EQ(2, c.changeState());
	ostringstream o;
	o << c;
	ASSERT_EQ("0", o.str());
}

TEST(FredkinCellFixture, fredkin_cell_custom_constructor_2) {
	FredkinCell c(false, '0');
	ASSERT_EQ(0,c.isAlive(0));
}

TEST(FredkinCellFixture, fredkin_cell_custom_constructor_3) {
	FredkinCell c(false, '-');
	ASSERT_EQ(0,c.isAlive(0));
}

TEST(FredkinCellFixture, fredkin_cell_clone_1) {
	AbstractCell *c = new FredkinCell();
	AbstractCell *p = c->clone();
	ASSERT_NE(c, p);
	ASSERT_EQ(c->changeState(), p->changeState());
}

TEST(FredkinCellFixture, fredkin_cell_clone_2) {
	AbstractCell *c = new FredkinCell(false, '-');
	AbstractCell *p = c->clone();
	ASSERT_NE(c, p);
	ASSERT_EQ(c->changeState(), p->changeState());
}

TEST(FredkinCellFixture, fredkin_cell_clone_3) {
	AbstractCell *c = new FredkinCell(true, '0');
	AbstractCell *p = c->clone();
	ASSERT_NE(c, p);
	ASSERT_EQ(c->changeState(), p->changeState());
}

TEST(FredkinCellFixture, fredkin_cell_evolve_Life_Cell_1) {
	Life<Cell> l;
	Cell c = l.at(15);
	c.evolve(15, l);
	ASSERT_EQ(1, c.isAlive(0));
}

TEST(FredkinCellFixture, fredkin_cell_evolve_Life_Cell_2) {
	Life<Cell> l;
	Cell c = l.at(20);
	c.evolve(20, l);
	ASSERT_EQ(1, c.isAlive(0));
}

TEST(FredkinCellFixture, fredkin_cell_evolve_Life_Cell_3) {
	Life<Cell> l;
	Cell c = l.at(15);
	c.evolve(15, l);
	ASSERT_EQ(1, c.isAlive(0));
}

TEST(FredkinCellFixture, fredkin_cell_evolve_Life_FredkinCell_1) {
	Life<FredkinCell> l;
	FredkinCell c = l.at(0);
	c.evolve(0, l);
	ASSERT_EQ(0, c.isAlive(0));
}

TEST(FredkinCellFixture, fredkin_cell_evolve_Life_FredkinCell_2) {
	Life<FredkinCell> l;
	FredkinCell c = l.at(20);
	c.evolve(20, l);
	ASSERT_EQ(0, c.isAlive(0));
}

TEST(FredkinCellFixture, fredkin_cell_evolve_Life_FredkinCell_3) {
	Life<ConwayCell> l;
	ConwayCell c = l.at(15);
	c.evolve(15, l);
	ASSERT_EQ(0, c.isAlive(0));
}

// CellFixture

TEST(CellFixture, cell_default_constructor_1) {
	FredkinCell fc;
	Cell c;
	ASSERT_EQ(fc.isAlive(0), c.isAlive(0));
}
TEST(CellFixture, cell_default_constructor_2) {
	FredkinCell fc(true, '0');
	Cell c;
	ASSERT_NE(fc.isAlive(0), c.isAlive(0));
}
TEST(CellFixture, cell_default_constructor_3) {
	FredkinCell fc(false, '-');
	Cell c;
	ASSERT_EQ(fc.isAlive(0), c.isAlive(0));
}

TEST(CellFixture, cell_abstractCell_constructor_1) {
	FredkinCell fc;
	Cell c = new FredkinCell();
	ASSERT_EQ(fc.isAlive(0), c.isAlive(0));
}
TEST(CellFixture, cell_abstractCell_constructor_2) {
	ConwayCell cc;
	Cell c = new ConwayCell();
	ASSERT_EQ(cc.isAlive(0), c.isAlive(0));
}
TEST(CellFixture, cell_abstractCell_constructor_3) {
	FredkinCell fc;
	Cell c = new FredkinCell(false, '-');
	ASSERT_EQ(fc.isAlive(0), c.isAlive(0));
}
TEST(CellFixture, cell_abstractCell_constructor_4) {
	ConwayCell cc;
	Cell c = new ConwayCell(false, '.');
	ASSERT_EQ(cc.isAlive(0), c.isAlive(0));
}
TEST(CellFixture, cell_abstractCell_constructor_5) {
	FredkinCell fc(true, '0');
	Cell c = new FredkinCell();
	ASSERT_NE(fc.isAlive(0), c.isAlive(0));
}
TEST(CellFixture, cell_abstractCell_constructor_6) {
	ConwayCell cc(true, '*');
	Cell c = new ConwayCell();
	ASSERT_NE(cc.isAlive(0), c.isAlive(0));
}
TEST(CellFixture, cell_abstractCell_constructor_7) {
	FredkinCell fc(true, '0');
	Cell c = new FredkinCell(true, '0');
	ASSERT_EQ(fc.isAlive(0), c.isAlive(0));
}
TEST(CellFixture, cell_abstractCell_constructor_8) {
	ConwayCell cc(true, '*');
	Cell c = new ConwayCell(true, '*');
	ASSERT_EQ(cc.isAlive(0), c.isAlive(0));
}

TEST(CellFixture, cell_custom_constructor_1) {
	FredkinCell fc;
	Cell c(false, '-');
	ASSERT_EQ(fc.isAlive(0), c.isAlive(0));
}
TEST(CellFixture, cell_custom_constructor_2) {
	ConwayCell cc;
	Cell c(false, '.');
	ASSERT_EQ(cc.isAlive(0), c.isAlive(0));
}
TEST(CellFixture, cell_custom_constructor_3) {
	FredkinCell fc;
	Cell c(true, '0');
	ASSERT_NE(fc.isAlive(0), c.isAlive(0));
}
TEST(CellFixture, cell_custom_constructor_4) {
	ConwayCell cc;
	Cell c(true, '*');
	ASSERT_NE(cc.isAlive(0), c.isAlive(0));
}

TEST(CellFixture, cell_assignment_operator_1) {
	Cell c = new FredkinCell();
	Cell p;
	c = p;
	ASSERT_EQ(c.isAlive(0), p.isAlive(0));
}
TEST(CellFixture, cell_assignment_operator_2) {
	Cell c = new ConwayCell();
	Cell p;
	c = p;
	ASSERT_EQ(c.isAlive(0), p.isAlive(0));
}
TEST(CellFixture, cell_assignment_operator_3) {
	Cell c = new FredkinCell(true, '0');
	Cell p;
	c = p;
	ASSERT_EQ(c.isAlive(0), p.isAlive(0));
}
TEST(CellFixture, cell_assignment_operator_4) {
	Cell c = new ConwayCell(true, '*');
	Cell p;
	c = p;
	ASSERT_EQ(c.isAlive(0), p.isAlive(0));
}

TEST(CellFixture, cell_evolve_1) {
	Life<Cell> l;
	Cell c = l.at(27);
	c.evolve(27, l);
	ASSERT_EQ(1, c.isAlive(0));
}
TEST(CellFixture, cell_evolve_2) {
	Life<Cell> l;
	Cell c = l.at(0);
	c.evolve(0, l);
	ASSERT_EQ(1, c.isAlive(0));
}
TEST(CellFixture, cell_evolve_3) {
	Life<Cell> l;
	Cell c = l.at(99);
	c.evolve(99, l);
	ASSERT_EQ(1, c.isAlive(0));
}

TEST(CellFixture, cell_canMutate_1) {
	Life<Cell> l;
	Cell c = l.at(27);
	ASSERT_FALSE(c.canMutate());
}
TEST(CellFixture, cell_canMutate_2) {
	Life<Cell> l;
	Cell c = l.at(0);
	ASSERT_FALSE(c.canMutate());
}
TEST(CellFixture, cell_canMutate_3) {
	Life<Cell> l;
	Cell c = l.at(99);
	ASSERT_FALSE(c.canMutate());
}

TEST(CellFixture, cell_changeState_1) {
	Cell c;
	ASSERT_EQ(0, c.changeState());
}
TEST(CellFixture, cell_changeState_2) {
	Cell c = new ConwayCell();
	ASSERT_EQ(0, c.changeState());
}
TEST(CellFixture, cell_changeState_3) {
	Cell c = new FredkinCell(true, '0');
	ASSERT_EQ(2, c.changeState());
}
TEST(CellFixture, cell_changeState_4) {
	Cell c = new ConwayCell(true, '*');
	ASSERT_EQ(2, c.changeState());
}

TEST(CellFixture, cell_isAlive_1) {
	Cell c;
	ASSERT_EQ(0, c.isAlive(0));
}
TEST(CellFixture, cell_isAlive_2) {
	Cell c = new ConwayCell();
	ASSERT_EQ(0, c.isAlive(0));
}
TEST(CellFixture, cell_isAlive_3) {
	Cell c = new FredkinCell(true, '0');
	ASSERT_NE(0, c.isAlive(0));
}
TEST(CellFixture, cell_isAlive_4) {
	Cell c = new ConwayCell(true, '*');
	ASSERT_NE(0, c.isAlive(0));
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
	Life<Cell> l;
	Cell c = l.at(0);
	ASSERT_EQ(1, c.isAlive(0));
}
TEST(LifeFixture, Life_default_constructor_2) {
	Life<ConwayCell> l;
	ConwayCell c = l.at(0);
	ASSERT_EQ(0, c.isAlive(0));
}
TEST(LifeFixture, Life_default_constructor_3) {
	Life<FredkinCell> l;
	FredkinCell c = l.at(0);
	ASSERT_EQ(0, c.isAlive(0));
}

TEST(Life, Life_custom_constructor_1) {
	vector<char> g(1, '-');
	Life<Cell> l(1, 1, g);
	Cell c = l.at(0);
	ASSERT_EQ(0, c.isAlive(0));
}
TEST(Life, Life_custom_constructor_2) {
	vector<char> g(1, '0');
	Life<Cell> l(1, 1, g);
	Cell c = l.at(0);
	ASSERT_NE(0, c.isAlive(0));
}
TEST(Life, Life_custom_constructor_3) {
	vector<char> g(1, '.');
	Life<ConwayCell> l(1, 1, g);
	ConwayCell c = l.at(0);
	ASSERT_EQ(0, c.isAlive(0));
}
TEST(Life, Life_custom_constructor_4) {
	vector<char> g(1, '*');
	Life<ConwayCell> l(1, 1, g);
	ConwayCell c = l.at(0);
	ASSERT_NE(0, c.isAlive(0));
}
TEST(Life, Life_custom_constructor_5) {
	vector<char> g(1, '-');
	Life<FredkinCell> l(1, 1, g);
	FredkinCell c = l.at(0);
	ASSERT_EQ(0, c.isAlive(0));
}
TEST(Life, Life_custom_constructor_6) {
	vector<char> g(1, '0');
	Life<FredkinCell> l(1, 1, g);
	FredkinCell c = l.at(0);
	ASSERT_NE(0, c.isAlive(0));
}

TEST(LifeFixture, Life_runLife_1) {
	vector<char> g(1, '-');
	Life<Cell> l(1, 1, g);
	l.runLife();
	ostringstream o;
	o << l << endl;
	string s = "Population = 0.\n-\n\n";
	ASSERT_EQ(s, o.str());
}
TEST(LifeFixture, Life_runLife_2) {
	vector<char> g(1, '0');
	Life<Cell> l(1, 1, g);
	l.runLife();
	ostringstream o;
	o << l << endl;
	string s = "Population = 0.\n-\n\n";
	ASSERT_EQ(s, o.str());
}
TEST(LifeFixture, Life_runLife_3) {
	vector<char> g(1, '.');
	Life<Cell> l(1, 1, g);
	l.runLife();
	ostringstream o;
	o << l << endl;
	string s = "Population = 0.\n.\n\n";
	ASSERT_EQ(s, o.str());
}
TEST(LifeFixture, Life_runLife_4) {
	vector<char> g(1, '*');
	Life<Cell> l(1, 1, g);
	l.runLife();
	ostringstream o;
	o << l << endl;
	string s = "Population = 0.\n.\n\n";
	ASSERT_EQ(s, o.str());
}
TEST(LifeFixture, Life_runLife_5) {
	vector<char> g(1, '.');
	Life<ConwayCell> l(1, 1, g);
	l.runLife();
	ostringstream o;
	o << l << endl;
	string s = "Population = 0.\n.\n\n";
	ASSERT_EQ(s, o.str());
}
TEST(LifeFixture, Life_runLife_6) {
	vector<char> g(1, '*');
	Life<ConwayCell> l(1, 1, g);
	l.runLife();
	ostringstream o;
	o << l << endl;
	string s = "Population = 0.\n.\n\n";
	ASSERT_EQ(s, o.str());
}
TEST(LifeFixture, Life_runLife_7) {
	vector<char> g(1, '-');
	Life<FredkinCell> l(1, 1, g);
	l.runLife();
	ostringstream o;
	o << l << endl;
	string s = "Population = 0.\n-\n\n";
	ASSERT_EQ(s, o.str());
}
TEST(LifeFixture, Life_runLife_8) {
	vector<char> g(1, '0');
	Life<FredkinCell> l(1, 1, g);
	l.runLife();
	ostringstream o;
	o << l << endl;
	string s = "Population = 0.\n-\n\n";
	ASSERT_EQ(s, o.str());
}

TEST(LifeFixture, Life_inspectNeighbors_1) {
	vector<char> g(1, '0');
	Life<Cell> l(1, 1, g);
	ASSERT_FALSE(l.inspectNeighbors(0, '0'));
}
TEST(LifeFixture, Life_inspectNeighbors_2) {
	vector<char> g(1, '.');
	Life<ConwayCell> l(1, 1, g);
	ASSERT_FALSE(l.inspectNeighbors(1, '.'));
}
TEST(LifeFixture, Life_inspectNeighbors_3) {
	vector<char> g(1, '-');
	Life<FredkinCell> l(1, 1, g);
	ASSERT_FALSE(l.inspectNeighbors(1, '-'));
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

TEST(LifeFixture, Life_begin_1) {
	Life<ConwayCell> l;
	L_Iterator<int> b = l.begin();
	ASSERT_EQ(0, *b);
}
TEST(LifeFixture, Life_begin_2) {
	Life<FredkinCell> l;
	L_Iterator<int> b = l.begin();
	ASSERT_EQ(0, *b);
}
TEST(LifeFixture, Life_begin_3) {
	Life<Cell> l;
	L_Iterator<int> b = l.begin();
	ASSERT_EQ(0, *b);
}

TEST(LifeFixture, Life_end_1) {
	Life<ConwayCell>l;
	L_Iterator<int> e = l.end();
	ASSERT_EQ(100, *e);
}
TEST(LifeFixture, Life_end_2) {
	Life<FredkinCell>l;
	L_Iterator<int> e = l.end();
	ASSERT_EQ(100, *e);
}
TEST(LifeFixture, Life_end_3) {
	Life<Cell>l;
	L_Iterator<int> e = l.end();
	ASSERT_EQ(100, *e);
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



// g++ -fprofile-arcs -ftest-coverage -pedantic -std=c++11 -Wall Life.c++ TestLife.c++ -o TestLife -lgtest -lgtest_main -lpthread
