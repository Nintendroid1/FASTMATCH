#include "../include/Grid.hpp"

//For G
Grid::Grid(double d, double epsilon, vector<Vertex> aV) {
    delta = d;
    sideLength = (epsilon*delta)/(6*sqrt(2));
    allVertices = aV;

    sortVerticesX = aV;
    sortVerticesY = aV;

    //Sort on respective axis
    sort(sortVerticesX.begin(), sortVerticesX.end(), Point::compareX);
    sort(sortVerticesY.begin(), sortVerticesY.end(), Point::compareY);
}

//Determine Bounding square based on points
void Grid::determineBoundingSquare() {
    //TODO: Round?
    double minX = floor(sortVerticesX.front().getX());
    double maxX = ceil(sortVerticesX.back().getX());
    double minY = floor(sortVerticesY.front().getY());
    double maxY = ceil(sortVerticesY.back().getY());
    
    //Take the longer side
    double slack = abs(abs(minX - maxX) - abs(minY - maxY))/2;

    //Transform lower left bounding square to be origin (0,0) => (minX, minY)
    startX = minX - slack;
    startY = minY - slack;
    endX = maxX + slack;
    endY = maxY + slack;    
}

//Assign points to respective cells
void Grid::populateCells() {
    //Scan through all the vertices
    int j = 0;
    for(int i=0; i < (int)sortVerticesX.size(); i++) {
        Vertex curr = sortVerticesX[i];
        double currX = curr.getX();
        double currY = curr.getY();

        //Calculate interval vertex belongs in
        int k = 0;
        int originalJ = j;
        double intervalX = startX + (j * sideLength);
        double intervalY = startY + (k * sideLength);

        //Find row index in Grid
        while(currX <= intervalX && intervalX < endX) {
            j++;
            intervalX = startX + (j * sideLength);
        }
                
        //Find col index in Grid
        while(currY <= intervalY && intervalY < endY) {
            k++;
            intervalY = startY + (k * sideLength);
        }
        
        //Iterating through x values, so if it is in the same cell should have the same j as previous iteration
        //The most recent cell added should also be the only cell to check for the same k value
        if(originalJ == j && sortCellX.size() != 0 && sortCellX.back().getColIndex() == k) {
            //Add to Cell, snapped to center
            sortCellX.back().addVertex(curr);
        }
        else {
            //Create cell if it doesn't already exist
            Cell newCell(j, k, startX, startY, sideLength);
            newCell.createCenter();
            newCell.addVertex(curr);
            sortCellX.push_back(newCell);
        }
    }
}

void Grid::formEdges() {
    //Iterate through cells
    //Implicitly sorted by x
    for(int i = 0; i < (int)sortCellX.size(); i++) {
        Cell& curr = sortCellX[i];

        //Find neighbors within 2delta neighborhood, horizontal
        int start = bsCellX(0, i, curr.getCenterX() - delta);
        int end =   bsCellX(i, (int) sortCellX.size(), curr.getCenterX() + delta) + 1;

        for(int j = start; j < end; j++) {
            if(i == j) {
                continue;
            }
            Cell* neighbor = &sortCellX[j];
            // Vertex* nA = neighbor.getPointerVertexA();
            // Vertex* nB = neighbor.getPointerVertexB();

            //Ignore when center point doesn't exist
            if(curr.getCellStatus() == ASET) {  
                curr.formEdgeA(neighbor);
            }
            else if(curr.getCellStatus() == BSET) {
                curr.formEdgeB(neighbor);
            }
            else {//curr.getCellStatus() == ALL
                curr.formEdgeA(neighbor);
                curr.formEdgeB(neighbor);
            }
        }
    }
    sortCellY = sortCellX;
    sort(sortCellY.begin(), sortCellY.end(), Cell::compareCenterY);
    for(int i = 0; i < (int)sortCellY.size(); i++) {
        Cell& curr = sortCellY[i];

        //Find neighbors within 2delta neighborhood, vertical
        int start = bsCellY(0, i, curr.getCenterY() - delta);
        int end =   bsCellY(i, (int) sortCellY.size(), curr.getCenterY() + delta)+1;

        //TODO Repeats?
        for(int j = start; j < end; j++) {
            if(i == j) {
                continue;
            }
            Cell* neighbor = &sortCellY[j];
            // Vertex* nA = neighbor.getPointerVertexA();
            // Vertex* nB = neighbor.getPointerVertexB();

            //Ignore when center point doesn't exist
            if(curr.getCellStatus() == ASET) {  
                curr.formEdgeA(neighbor);
            }
            else if(curr.getCellStatus() == BSET) {
                curr.formEdgeB(neighbor);
            }
            else {//curr.getCellStatus() == ALL
                curr.formEdgeA(neighbor);
                curr.formEdgeB(neighbor);
            }
        }
    }

}

//Iterative binary search for row index in Cells
int Grid::bsCellX(int l, int r, double x) { 
    //Start at Center
    int m = l + (r - l) / 2;

    while (l <= r) { 
        // cout << x << " : " << m << endl;
        m = l + (r - l) / 2; 
  
        // Check if x is present at mid 
        if (sortCellX[m].getCenterX() == x) {
            return m; 
        }
  
        // If x greater, ignore left half 
        else if (sortCellX[m].getCenterX() < x) {
            l = m + 1; 
        }
        // If x is smaller, ignore right half 
        else {
            r = m - 1; 
        }
    } 

    if(m < 0) {
        return 0;
    }
    else if (m > (int)sortCellX.size() - 1) {
        return sortCellX.size() - 1;
    }

    //Only care about interval x exists in 
    return m; 
} 

//Iterative binary search for row index in Cells
int Grid::bsCellY(int l, int r, double y) { 
    //Start at center
    int m = l + (r - l) / 2;

    while (l <= r) { 
        m = l + (r - l) / 2; 
  
        // Check if x is present at mid 
        if (sortCellY[m].getCenterY() == y) {
            return m; 
        }
  
        // If x greater, ignore left half 
        else if (sortCellY[m].getCenterY() < y) {
            l = m + 1; 
        }
  
        // If x is smaller, ignore right half 
        else {
            r = m - 1; 
        }
    } 

    if(m < 0) {
        return 0;
    }
    else if (m > (int)sortCellY.size() - 1) {
        return sortCellY.size() - 1;
    }
    //Only care about interval y exists in 
    return m; 
}
