#include "../include/Grid.hpp"

//For G
Grid::Grid(double d, double epsilon) {
    delta = d;
    sideLength = (epsilon*delta)/(6*sqrt(2));
}

//Assign points to respective cells
void Grid::populateCells(vector<Vertex> allVertices) {
    vector<Vertex> sortVerticesX(allVertices);
    vector<Vertex> sortVerticesY(allVertices);

    //Sort on respective axis
    sort(sortVerticesX.begin(), sortVerticesX.end(), Point::compareX);
    sort(sortVerticesY.begin(), sortVerticesY.end(), Point::compareY);

    //Form edges on neighborhood
    for(int i=0; i < (int)allVertices.size(); i++) {
        Vertex curr = allVertices[i];
        
    }
}

