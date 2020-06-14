#include "../include/Cell.hpp"

Cell::Cell(int row, int col, double d, double sideLength) 
    : vertexA(A, 0.0,0.0), vertexB(B, 0.0,0.0) {
    rowIndex = row;
    colIndex = col;
    delta = d;
    cellLength = sideLength;
    cellStatus = NONE;
}

//TODO Can't be negative
void Cell::createCenter() {
    //Snap points to center
    double midLength = cellLength/2;

    //Assumes 2delta bounding square
    centerX = (-delta) + (rowIndex * cellLength) + midLength;
    centerY = (-delta) + (colIndex * cellLength) + midLength;

    //Initialize weight 0 since no vertices yet
    vertexA = Vertex(A, centerX, centerY);
    vertexB = Vertex(B, centerX, centerY);
}

//Add vertex to overall list and based on specific class
void Cell::addVertex(Vertex v) {
    if(v.getLabel() == A) {
        //At least one vertex of class A
        vertexA.updateWeight();

        //Update Cell's Status relative to A
        if(cellStatus == NONE) {
            cellStatus = ASET;
        }
        else if(cellStatus == BSET) {
            cellStatus = ALL;
        }
    }
    else {//v.getLabel() == B
        //At least one vertex of class B
        vertexB.updateWeight();

        //Update Cell's Status relative to B
        if(cellStatus == NONE) {
            cellStatus = BSET;
        }
        else if(cellStatus == ASET) {
            cellStatus = ALL;
        }
    }
}

//Returns true if this cell has a lesser x value
bool Cell::compareCenterX(Cell const & c1, Cell const & c2) {
    return Point::compareX(c1.getVertexA(), c2.getVertexA()); //A or B is fine, same coordinates
}

//Returns true if this cell has a lesser y value
bool Cell::compareCenterY(Cell const & c1, Cell const & c2) {
    return Point::compareY(c1.getVertexA(), c2.getVertexA()); //A or B is fine, same coordinates
}
