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
    double minX = round(sortVerticesX.front().getX());
    double maxX = round(sortVerticesX.back().getX());
    double minY = round(sortVerticesY.front().getY());
    double maxY = round(sortVerticesY.back().getY());
    
    double minLength = 0;
    double maxLength = 0;

    //Take the longer side
    if(abs(minX - maxX) > abs(minY - maxY)) {
        minLength = minX;
        maxLength = maxX;
    } else {
        minLength = minY;
        maxLength = maxY;  
    }

    //Calculated intervals
    double startX = minLength;
    double startY = minLength;

    intervalX.push_back(startX);
    intervalY.push_back(startY);


    while(startX < maxLength) {
        startX += sideLength;
       intervalX.push_back(min(startX, delta));
    }

    while(startY < maxLength) {
        startY += sideLength;
        intervalY.push_back(min(startY, delta));
    }
}
// //Assign points to respective cells
// void Grid::populateCells() {
//     //Scan through all the vertices
//     for(int i=0; i < (int)sortVerticesX.size(); i++) {
//         Vertex curr = sortVerticesX[i];

//         //Find row index in Grid
//         for(int j = 1; j <(int)intervalX.size(); j++) {
//             if(curr.getX() < intervalX[j]) {

//                 //Find col index in Grid
//                 for(int k = 1; k <(int)intervalY.size(); k++) {
//                     if(curr.getY() < intervalY[k]) {
//                         bool added = false;
//                         for(int l = 0; l <(int)cells.size(); l++) {
//                             if(cells[l].getRowIndex() == j && cells[l].getColIndex() == k) {
//                                 //Add to Cell, snapped to center
//                                 cells[l].addVertex(curr);
//                                 added = true;
//                                 break;
//                             }
//                         }
//                         if(!added) {
//                             //Create cell if it doesn't already exist
//                             Cell newCell(j, k, delta, sideLength);
//                             newCell.createCenter();
//                             // cout << "Point: " << curr.getX() << " " << curr.getY() << endl;
//                             // cout << "Celllength: " << sideLength << endl;
//                             // cout << "j = " << j << " k = " << k << endl;
//                             // cout << "Interval: " << intervalX[j] << " " << intervalY[k] << endl;
//                             // cout << "Cell: " << newCell.getCenterX() << " " << newCell.getCenterY() << endl << endl;
//                             cells.push_back(newCell);
//                         }
                        
//                         break;
//                     }
//                 }
//                 break;
//             }
//         }
//     }
// }

//Assign points to respective cells
void Grid::populateCells() {
    //Scan through all the vertices
    for(int i=0; i < (int)sortVerticesX.size(); i++) {
        Vertex curr = sortVerticesX[i];

        //Find row index in Grid
        int j = bsBoundX(0, intervalX.size() - 1, curr.getX());
                
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
            Cell newCell(j, k, delta, sideLength);
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
        int start = bsCellX(0, (int) sortCellX.size(), curr.getCenterX() - delta);
        int end =   bsCellX(0, (int) sortCellX.size(), curr.getCenterX() + delta);

        for(int j = start; j < end; j++) {
            if(i == j) {
                continue;
            }
            Cell neighbor = sortCellX[j];
            //Ignore when center point doesn't exist
            if(curr.getCellStatus() == ASET) {  
                curr.modVertexA().addEdge(neighbor.getVertexB());
            }
            else if(curr.getCellStatus() == BSET) {
                curr.modVertexB().addEdge(neighbor.getVertexA());
            }
            else {//curr.getCellStatus() == ALL
                curr.modVertexA().addEdge(neighbor.getVertexB());
                curr.modVertexB().addEdge(neighbor.getVertexA());
            }
        }
    }

    vector<Cell> sortCellY(sortCellX);
    sort(sortCellY.begin(), sortCellY.end(), Cell::compareCenterY);
    for(int i = 0; i < (int)sortCellY.size(); i++) {
        Cell& curr = sortCellY[i];

        //Find neighbors within 2delta neighborhood, vertical
        int start = bsCellY(0, (int) sortCellY.size(), curr.getCenterY() - delta);
        int end =   bsCellY(0, (int) sortCellY.size(), curr.getCenterY() + delta);

        //TODO Repeats?
        for(int j = start; j < end; j++) {
            if(i == j) {
                continue;
            }
            Cell neighbor = sortCellY[j];
            //Ignore when center point doesn't exist
            if(curr.getCellStatus() == ASET) {  
                curr.modVertexA().addEdge(neighbor.getVertexB());
            }
            else if(curr.getCellStatus() == BSET) {
                curr.modVertexB().addEdge(neighbor.getVertexA());
            }
            else {//curr.getCellStatus() == ALL
                curr.modVertexA().addEdge(neighbor.getVertexB());
                curr.modVertexB().addEdge(neighbor.getVertexA());
            }
        }
    }

}

//Iterative binary search for row index in Cells
int Grid::bsCellX(int l, int r, double x) { 
    //Start at Center
    int m = l + (r - l) / 2;

    while (l <= r) { 
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
