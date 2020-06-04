#ifndef GRIDPRIME
#define GRIDPRIME

#include <stdio.h>
#include <vector>
#include <math.h> 
#include "Grid.hpp"

using namespace std;

/*
* Contains cells and is within a bounding square
*/
class GridPrime {
    private:
        //Generate cells xi based on sidelength
        vector<Cell> cells;
        int sideLength;
        double delta;
        double epsilon;
        int r;

    public:
        //For G'
        GridPrime(double d, double e, int rr);

        void populateCells(vector<Vertex> allVertices);

        //Find subset of cells N(xi) such that their minimum distance is delta
        //Need to be within bounding box but need to be within range
        vector<Cell> getSubset(int index);

        //Any cell of G is a boundary cell xi with respect to G' if there is a cell xi'
        //in subset of xi such that they are not the same cell
        void checkBoundaryCells(Grid g);

        //Make G' such that the number of boundary points is O(n/(\epsilon*sqrt(r))))
        void constructGridPrime(Grid g);

        double getDelta() {return delta;}
        
        double getEpsilon() {return epsilon;}

        vector<Cell> getCells() {return cells;}

        double getR() {return r;}

};
#endif