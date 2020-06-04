#include "../include/Grid.hpp"

//For G
Grid::Grid(double d, double epsilon) {
    delta = d;
    sideLength = (int)ceil((epsilon*delta)/(6*sqrt(2)));
}

void Grid::populateCells(vector<Vertex> allVertices) {
    //TODO Can Cells be empty?
    for(int i=0; i < allVertices.size(); i++) {
        //TODO Add to corresponding cell
    }
}

//Find subset of cells N(xi) such that their minimum distance is delta
//Need to be within bounding box but need to be within range
vector<Cell> Grid::getSubset(int index) {
    int start = (int)max(0, (int)floor(index-delta));
    int end = (int)min((int)floor(index+delta), (int)cells.size());
    vector<Cell> subList(&cells[start], &cells[end]);

    return subList;

}

//Construct bipartite graph
//Add an edge in the graph between two points (a,b) of in different cells if it exists in the respective subgraph
//delta is at least the bottleneck distance, so H will have a perfect matching
void Grid::checkAddEdge(Cell curr, vector<Vertex> allVertices) {
    //Check if current cell is active
    if(curr.isActive(allVertices)) {
        //Get the sublist of the current cell
        vector<Cell> currSub = getSubset(curr.getCellIndex());

        //Iterate through sublist
        for(int i=0; i < currSub.size(); i++) {
            Cell thisSub = currSub[i];

            //Same cell
            if(curr.getCellIndex() == thisSub.getCellIndex()) {
                continue;
            }
            
            //TODO Other way?
            vector<Vertex> currB = curr.getVertexB();
            vector<Vertex> subA = thisSub.getVertexA();
            
            for(int j=0; j < currB.size(); j++) {
                for(int k=0; k < subA.size(); k++) {
                    currB[j].addEdge(subA[k]);
                }
                
            }
        }
    }
}

