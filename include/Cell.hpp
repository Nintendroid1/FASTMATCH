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

        double centerX;
        double centerY;

        double minX;
        double minY;

        //sideLength of cell
        double cellLength;

        //Indicates if empty, single class, or both classes
        Status cellStatus;
    public:
        Cell(int row, int col, double mX, double mY, double sideLength);
        
        void createCenter();

        //Add vertex to overall list and based on specific class
        void addVertex(Vertex v);
        void formEdgeA(Vertex vB);
        void formEdgeB(Vertex vA);

        static bool compareCenterX(Cell const & c1, Cell const & c2);
        static bool compareCenterY(Cell const & c1, Cell const & c2);

        Vertex getVertexA() const {return vertexA;}
        Vertex getVertexB() const {return vertexB;}
        int getRowIndex() const {return rowIndex;}
        int getColIndex() const {return colIndex;}
        double getCellLength() const {return cellLength;}
        Status getCellStatus() const {return cellStatus;}
        double getCenterX() const {return centerX;}
        double getCenterY() const {return centerY;}
};
#endif