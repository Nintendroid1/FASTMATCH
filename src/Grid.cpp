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

    //Calculated intervals
    startX = minX - slack;
    startY = minY - slack;
    double endX = maxX + slack;
    double endY = maxY + slack;

    intervalX.push_back(startX);
    intervalY.push_back(startY);

    double insert = startX;
    while(insert < endX) {
        insert += sideLength;
        intervalX.push_back(min(insert, endX));
    }

    insert = startY;
    while(insert < endY) {
        insert += sideLength;
        intervalY.push_back(min(insert, endY));
    }
}

//Assign points to respective cells
void Grid::populateCells() {
    //Scan through all the vertices
    for(int i=0; i < (int)sortVerticesX.size(); i++) {
        Vertex curr = sortVerticesX[i];

        //Find row index in Grid
        int j = bsBoundX(i, intervalX.size() - 1, curr.getX());
                
        //Find col index in Grid
        int k = bsBoundY(0, intervalY.size() - 1, curr.getY());

        bool added = false;
        for(int l = 0; l <(int)sortCellX.size(); l++) {
            if(sortCellX[l].getRowIndex() == j && sortCellX[l].getColIndex() == k) {
                //Add to Cell, snapped to center
                // cout << "Same Cell: " << j << " " << k << endl;
                // cout << curr.getX() << " " << curr.getY() << endl << endl;
                sortCellX[l].addVertex(curr);
                added = true;
                break;
            }
        }
        if(!added) {
            //Create cell if it doesn't already exist
            Cell newCell(j, k, startX, startY, sideLength);
            newCell.createCenter();
            newCell.addVertex(curr);
            // cout << "New Cell: " << j << " " << k << endl;
            // cout << "Point: " << curr.getX() << " " << curr.getY() << endl;
            // cout << "Celllength: " << sideLength << endl;
            // cout << "j = " << j << " k = " << k << endl;
            // cout << "Interval: " << intervalX[j] << " " << intervalY[k] << endl;
            // cout << "Cell: " << newCell.getCenterX() << " " << newCell.getCenterY() << endl << endl;
            sortCellX.push_back(newCell);
        }
    }
    // cout << allVertices.size() << " " << sortCellX.size() << endl;
    intervalX.clear();
    intervalY.clear();
}

//Iterative binary search for row index in bounding square
int Grid::bsBoundX(int l, int r, double x) { 
    //Start at Center
    int m = l + (r - l) / 2;

    while (l <= r) { 
        m = l + (r - l) / 2; 
  
        // Check if x is present at mid 
        if (intervalX[m] == x) {
            return m; 
        }
  
        // If x greater, ignore left half 
        else if (intervalX[m] < x) {
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
    else if (m > (int)intervalX.size() - 1) {
        return intervalX.size() - 1;
    }

    //Only care about interval x exists in 
    return m; 
} 

//Iterative binary search for row index in bounding square
int Grid::bsBoundY(int l, int r, double y) { 
    //Start at center
    int m = l + (r - l) / 2;

    while (l <= r) { 
        m = l + (r - l) / 2; 
  
        // Check if x is present at mid 
        if (intervalY[m] == y) {
            return m; 
        }
  
        // If x greater, ignore left half 
        else if (intervalY[m] < y) {
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
    else if (m > (int)intervalY.size() - 1) {
        return intervalY.size() - 1;
    }
    //Only care about interval y exists in 
    return m; 
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
            Cell& neighbor = sortCellX[j];
            Vertex* nA = neighbor.getPointerVertexA();
            Vertex* nB = neighbor.getPointerVertexB();

            //Ignore when center point doesn't exist
            if(curr.getCellStatus() == ASET) {  
                curr.formEdgeA(nB);
            }
            else if(curr.getCellStatus() == BSET) {
                curr.formEdgeB(nA);
            }
            else {//curr.getCellStatus() == ALL
                curr.formEdgeA(nB);
                curr.formEdgeB(nA);
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
            Cell& neighbor = sortCellY[j];
            Vertex* nA = neighbor.getPointerVertexA();
            Vertex* nB = neighbor.getPointerVertexB();

            //Ignore when center point doesn't exist
            if(curr.getCellStatus() == ASET) {  
                curr.formEdgeA(nB);
            }
            else if(curr.getCellStatus() == BSET) {
                curr.formEdgeB(nA);
            }
            else {//curr.getCellStatus() == ALL
                curr.formEdgeA(nB);
                curr.formEdgeB(nA);
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
