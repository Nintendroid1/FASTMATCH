#ifndef GRID
#define GRID

#include <stdio.h>
#include <iostream>
#include <algorithm>
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
        //Implicitly sorted by the cell's center x-coordinate
        vector<Cell> cells;
        double sideLength;
        double delta;

    public:
        //For G
        Grid(double d, double epsilon);

        void populateCells(vector<Vertex> allVertices);
        void formEdges();

        vector<Cell> getCells() const {return cells;}
        double getSideLength() const {return sideLength;}
        double getDelta() const {return delta;}
};
#endif