#include "../include/GridGen.hpp"

GridGen::GridGen(double e, vector<double> ar){
    epsilon = e;
    alphaRange = ar;
}

//Iterate through possible delta values from alphaRange to generate G
//TODO Parallize
void GridGen::iterateAlpha(vector<Vertex> allVertices) {
    for(int i=0; i< (int)alphaRange.size(); i++) {
        Grid g = generateG(alphaRange[i], allVertices);
    }
}

Grid GridGen::generateG(double d, vector<Vertex> allVertices) {
    Grid g = Grid(d, epsilon, allVertices);
    g.determineBoundingSquare();
    g.populateCells();
    g.formEdges();
    return g;
}

