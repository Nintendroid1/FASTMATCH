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

    //Calculated intervals
    vector<double> intervalX;
    vector<double> intervalY;
    double startX = -delta;
    double startY = -delta;

    intervalX.push_back(startX);
    intervalY.push_back(startY);


    while(startX < delta) {
        startX += sideLength;
       intervalX.push_back(min(startX, delta));
    }

    while(startY < delta) {
        startY += sideLength;
        intervalY.push_back(min(startY, delta));
    }

    //Scan through all the vertices
    for(int i=0; i < (int)sortVerticesX.size(); i++) {
        Vertex curr = sortVerticesX[i];

        //Find row index in Grid
        for(int j = 1; j <(int)intervalX.size(); j++) {
            if(curr.getX() < intervalX[j]) {

                //Find col index in Grid
                for(int k = 1; k <(int)intervalY.size(); k++) {
                    if(curr.getY() < intervalY[k]) {
                        bool added = false;
                        for(int l = 0; l <(int)cells.size(); l++) {
                            if(cells[l].getRowIndex() == j && cells[l].getColIndex() == k) {
                                //Add to Cell, snapped to center
                                cells[l].addVertex(curr);
                                added = true;
                                break;
                            }
                        }
                        if(!added) {
                            //Create cell if it doesn't already exist
                            Cell newCell(j, k, delta, sideLength);
                            newCell.createCenter();
                            // cout << "Point: " << curr.getX() << " " << curr.getY() << endl;
                            // cout << "Celllength: " << sideLength << endl;
                            // cout << "j = " << j << " k = " << k << endl;
                            // cout << "Interval: " << intervalX[j] << " " << intervalY[k] << endl;
                            // cout << "Cell: " << newCell.getVertexA().getX() << " " << newCell.getVertexA().getY() << endl << endl;
                            cells.push_back(newCell);
                        }
                        
                        break;
                    }
                }
                break;
            }
        }
    }
}

void Grid::formEdges() {
    //Iterate through cells
    //Implicitly sorted by x
    for(int i = 0; i < (int)cells.size(); i++) {
        Cell& curr = cells[i];

        //Look through neighborhood for edges
        int start = max(0, i-2);
        int end = min(i+2, (int) cells.size());

        for(int j = start; j < end; j++) {
            if(i == j) {
                continue;
            }
            Cell neighbor = cells[j];
            //Ignore when center point doesn't exist
            if(curr.getCellStatus() == ASET) {  
                curr.modVertexA().addEdge(neighbor.getVertexB());
            }
            else if(curr.getCellStatus() == BSET) {
                curr.modVertexB().addEdge(neighbor.modVertexA());
            }
            else {//curr.getCellStatus() == ALL
                curr.modVertexA().addEdge(neighbor.getVertexB());
                curr.modVertexB().addEdge(neighbor.getVertexA());
            }
        }
    }
}

