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
        int sideLength;
        double delta;

    public:
        Grid(double delta, double epsilon);
        void populateCells(vector<Vertex> allVertices);

        //Find subset of cells N(xi) such that their minimum distance is delta
        //Need to be within bounding box but need to be within range
        vector<Cell> getSubset(int index);

        //Add an edge in the graph between two points (a,b) of in different cells if it exists in the respective subgraph
        void checkAddEdge(Cell curr, vector<Vertex> allVertices);

        double getDelta() {return delta;}

        vector<Cell> getCells() {return cells;}

};
#endif