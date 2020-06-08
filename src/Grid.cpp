#include "../include/Grid.hpp"

//For G
Grid::Grid(double d, double epsilon) {
    delta = d;
    sideLength = (epsilon*delta)/(6*sqrt(2));
}

//Assign points to respective cells
void Grid::populateCells(vector<Vertex> allVertices) {
    for(int i=0; i < (int)allVertices.size(); i++) {
    }
}

