#ifndef CELL
#define CELL

#include <stdio.h>
#include <vector>
#include <math.h>

#include "Vertex.hpp"
#include "Status.hpp"
using namespace std;

/*
* Contains vertices from both class A and B
* Contained in a Grid
*/

class Cell {
    private:
        //Centerpoint of respective class
        Vertex vertexA;
        Vertex vertexB;

        //Location of cell within grid
        int rowIndex;
        int colIndex;

        double delta;

        //sideLength of cell
        double cellLength;

        //Indicates if empty, single class, or both classes
        Status cellStatus;
    public:
        Cell(int row, int col, double d, double sideLength);
        
        void createCenter();

        //Add vertex to overall list and based on specific class
        void addVertex(Vertex v);

        Vertex getVertexA() {return vertexA;}
        Vertex getVertexB() {return vertexB;}
        int getRowIndex() {return rowIndex;}
        int getColIndex() {return colIndex;}
        double getCellLength() {return cellLength;}
        Status getCellStatus() {return cellStatus;}
};
#endif