// Copyright 2020, Nathaniel Salazar, All rights reserved

#include "../include/Grid.hpp"

Grid::Grid(double d, double epsilon, std::vector<Vertex> aV) {
    delta = d;
    sideLength = (epsilon*delta)/(6*sqrt(2));

    verticesX = aV;
    verticesY = aV;

    // Sort on respective axis
    sort(verticesX.begin(), verticesX.end(), compareVertexX);
    sort(verticesY.begin(), verticesY.end(), compareVertexY);
}

Grid::~Grid() {
    verticesX.clear();
    verticesY.clear();
    cellsX.clear();
    cellsY.clear();
}

// Determine Bounding square based on points
void Grid::determineBoundingSquare() {
    double minX = floor(verticesX.front().x);
    double maxX = ceil(verticesX.back().x);
    double minY = floor(verticesY.front().y);
    double maxY = ceil(verticesY.back().y);

    // Take the longer side
    double slack = abs(abs(minX - maxX) - abs(minY - maxY))/2;

    // Transform lower left bounding square to be origin (0,0) => (minX, minY)
    startX = minX - slack;
    startY = minY - slack;
    endX = maxX + slack;
    endY = maxY + slack;
}

// Assign points to respective cells
void Grid::populateCells() {
    // Scan through all the vertices
    int j = 0;
    for (int i=0; i < static_cast<int>(verticesX.size()); i++) {
        Vertex curr = verticesX[i];
        double currX = curr.x;
        double currY = curr.y;
        Label currLabel = curr.label;

        // Calculate interval vertex belongs in
        int k = 0;
        int originalJ = j;
        double intervalX = startX + (j * sideLength);
        double intervalY = startY + (k * sideLength);

        // Find row index in Grid
        while (abs(currX - intervalX) > sideLength && intervalX < endX) {
            j++;
            intervalX = startX + (j * sideLength);
        }

        // Find col index in Grid
        while (abs(currY - intervalY) > sideLength && intervalY < endY) {
            k++;
            intervalY = startY + (k * sideLength);
        }

        // Iterating through x values, so if it is in the same cell
        // should have the same j as previous iteration
        if (originalJ == j && cellsX.size() != 0 &&
            cellsX.back()->getCenterY() == (intervalY + sideLength/2)) {
            // Add to Cell, snapped to center
            cellsX.back()->addVertex(currLabel);

        } else {
            // Create cell if it doesn't already exist
            std::shared_ptr<Cell> newCell = std::make_shared<Cell>();
            newCell->createCenter(j, k, startX, startY, sideLength);
            newCell->addVertex(currLabel);

            cellsX.push_back(newCell);
        }
    }

    cellsY = cellsX;
    sort(cellsY.begin(), cellsY.end(), comparePCellY);
}

void Grid::formEdges() {
    // Iterate through cells
    // Implicitly sorted by x
    for (int i = 0; i < static_cast<int>(cellsX.size()); i++) {
        std::shared_ptr<Cell> curr = cellsX[i];

        // Find neighbors within 2delta neighborhood, horizontal
        int start = bsCellX(0, i, curr->getCenterX() - delta);
        int end =   bsCellX(i, static_cast<int>(cellsX.size()),
                        curr->getCenterX() + delta) + 1;

        for (int j = start; j < end; j++) {
            if (i == j) {
                continue;
            }
            std::shared_ptr<Cell> neighbor = cellsX[j];

            // Ignore when center point doesn't exist
            if (curr->getStatus() == ASET) {
                curr->formEdgeA(neighbor);

            } else if (curr->getStatus() == BSET) {
                curr->formEdgeB(neighbor);

            } else {  // curr.getStatus() == ALL
                curr->formEdgeA(neighbor);
                curr->formEdgeB(neighbor);
            }
        }
    }
    for (int i = 0; i < static_cast<int>(cellsY.size()); i++) {
        std::shared_ptr<Cell> curr = cellsY[i];

        // Find neighbors within 2delta neighborhood, vertical
        int start = bsCellY(0, i, curr->getCenterY() - delta);
        int end =   bsCellY(i, static_cast<int>(cellsY.size()),
                            curr->getCenterY() + delta)+1;

        // TODO(Nintendroid1): Repeats?
        for (int j = start; j < end; j++) {
            if (i == j) {
                continue;
            }
            std::shared_ptr<Cell> neighbor = cellsY[j];

            // Ignore when center point doesn't exist
            if (curr->getStatus() == ASET) {
                curr->formEdgeA(neighbor);

            } else if (curr->getStatus() == BSET) {
                curr->formEdgeB(neighbor);

            } else {  // curr.getStatus() == ALL
                curr->formEdgeA(neighbor);
                curr->formEdgeB(neighbor);
            }
        }
    }
}

// Iterative binary search for row index in Cells
int Grid::bsCellX(int l, int r, double x) {
    // Start at Center
    int m = l + (r - l) / 2;

    while (l <= r) {
        m = l + (r - l) / 2;

        if (m < 0) {
            return 0;

        } else if (m > static_cast<int>(cellsX.size()) - 1) {
            return cellsX.size() - 1;
        }

        // Check if x is present at mid
        if (cellsX[m]->getCenterX() == x) {
            return m;

        } else if (cellsX[m]->getCenterX() < x) {
            // If x greater, ignore left half
            l = m + 1;
        } else {  // If x is smaller, ignore right half
            r = m - 1;
        }
    }
    // Only care about interval x exists in
    return m;
}

// Iterative binary search for row index in Cells
int Grid::bsCellY(int l, int r, double y) {
    // Start at center
    int m = l + (r - l) / 2;

    while (l <= r) {
        m = l + (r - l) / 2;

        if (m < 0) {
            return 0;

        } else if (m > static_cast<int>(cellsY.size()) - 1) {
            return cellsY.size() - 1;
        }

        // Check if x is present at mid
        if (cellsY[m]->getCenterY() == y) {
            return m;

        } else if (cellsY[m]->getCenterY() < y) {
            // If x greater, ignore left half
            l = m + 1;

        } else {  // If x is smaller, ignore right half
            r = m - 1;
        }
    }
    // Only care about interval y exists in
    return m;
}

Grid generateGrid(double d, double epsilon, std::vector<Vertex> aV) {
    Grid g(d, epsilon, aV);
    g.determineBoundingSquare();
    g.populateCells();
    g.formEdges();
    return g;
}

