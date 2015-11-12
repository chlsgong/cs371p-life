#include <iostream> // cin, cout

#include "Life.h"

// ----
// main
// ----

int main () {
    using namespace std;
    enact_life(cin);
    return 0;}

// g++ -pedantic -std=c++11 -Wall Life.c++ RunLife.c++ -o RunLife