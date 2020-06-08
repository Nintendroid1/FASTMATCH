#ifndef GRID
#define GRID

#include <stdio.h>
#include <vector>
#include <math.h> 
#include "Cell.hpp"

using namespace std;

/*
* Contains cells and is within a bounding square
*/
class Grid {
    private:
        //Generate cells xi based on sidelength
        vector<Cell> cells;
        double sideLength;
        double delta;

    public:
        //For G
        Grid(double d, double epsilon);

        void populateCells(vector<Vertex> allVertices);

        vector<Cell> getCells() {return cells;}
        double getSideLength() {return sideLength;}
        double getDelta() {return delta;}
};
#endif