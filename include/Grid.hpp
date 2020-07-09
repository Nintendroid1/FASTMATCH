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
        vector<Cell> sortCellX;
        vector<Cell> sortCellY;
        
        double sideLength;
        double delta;

        double startX;
        double startY;
        double endX;
        double endY;

        vector<Vertex> allVertices;
        vector<Vertex> sortVerticesX;
        vector<Vertex> sortVerticesY;

        int bsBoundX(int l, int r, double x);
        int bsBoundY(int l, int r, double y);
        int bsCellX(int l, int r, double x);
        int bsCellY(int l, int r, double y);   
    public:
        //For G
        Grid(double d, double epsilon, vector<Vertex> aV);

        void determineBoundingSquare();
        void populateCells();
        void formEdges();
        
        vector<Cell> getCells() const {return sortCellX;}
        double getSideLength() const {return sideLength;}
        double getDelta() const {return delta;}
};
#endif