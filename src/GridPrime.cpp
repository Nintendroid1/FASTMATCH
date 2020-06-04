#include "../include/GridPrime.hpp"

//For G'
GridPrime::GridPrime(double d, double e, int rr) {
    delta = d;
    epsilon = e;
    r = rr;
    sideLength = (int)ceil(sqrt(r)*((epsilon*delta)/(6*sqrt(2))));
}

void GridPrime::populateCells(vector<Vertex> allVertices) {
    //TODO Can Cells be empty?
    for(int i=0; i < allVertices.size(); i++) {
        //TODO Add to corresponding cell
    }
}

//Find subset of cells N(xi) such that their minimum distance is delta
//Need to be within bounding box but need to be within range
vector<Cell> GridPrime::getSubset(int index) {
    int start = (int)max(0, (int)floor(index-delta));
    int end = (int)min((int)floor(index+delta), (int)cells.size());
    vector<Cell> subList(&cells[start], &cells[end]);

    return subList;

}

//Any cell of G is a boundary cell xi with respect to G' if there is a cell xi'
//xi' in subset of xi such that they are not the same cell
void GridPrime::checkBoundaryCells(Grid g) {
}

//Make G' such that the number of boundary points is O(n/(\epsilon*sqrt(r))))
void GridPrime::constructGridPrime(Grid g) {
    //Generate the vertical lines for G'
    //Generate the horizontal lines for G'
    //Mark as boundary cells
    //Mark boundary vertices wrt boundary cells
    //Select an int k=argmin|A_i \union B_i| and use k vertical lines
}

