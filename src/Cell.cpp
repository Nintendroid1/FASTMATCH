// Copyright 2020, Nathaniel Salazar, All rights reserved

#include "../include/Cell.hpp"

Cell::Cell() {
    weightA = 0;
    weightB = 0;
    capacity = 0.0;
    status = NONE;
    free = true;
    distance = 0.0;
}

Cell::~Cell() {
    edgesToA.clear();
    edgesToB.clear();
}

void Cell::createCenter(int row, int col,
    double minX, double minY, double cellLength) {

    // Snap points to center
    double midLength = cellLength/2;

    // Assumes 2delta bounding square
    centerX = minX + (row * cellLength) + midLength;
    centerY = minY + (col * cellLength) + midLength;
}

// Add vertex to overall list and based on specific class
void Cell::addVertex(Label l) {
    if (l == A) {
        // At least one vertex of class A
        weightA++;

        // Update Cell's Status relative to A
        if (status == NONE) {
            status = ASET;

        } else if (status == BSET) {
            status = ALL;
        }
    } else {  // l == B
        // At least one vertex of class B
        weightB++;

        // Update Cell's Status relative to B
        if (status == NONE) {
            status = BSET;
        } else if (status == ASET) {
            status = ALL;
        }
    }
}

// Add edge between this center's vertex A
void Cell::formEdgeA(std::weak_ptr<Cell> cB) {
    edgesToA.push_back(cB);
}

// Add edge between this center's vertex B
void Cell::formEdgeB(std::weak_ptr<Cell> cA) {
    edgesToB.push_back(cA);
}

void Cell::setMatch(std::weak_ptr<Cell> c) {
    match = c;
    free = false;
}

void Cell::setDistance(double d) {
    distance = d;
}

bool compareCellX(Cell const& lhs, Cell const& rhs) {
    return lhs.getCenterX() < rhs.getCenterX();
}

bool compareCellY(Cell const& lhs, Cell const& rhs) {
    return lhs.getCenterY() < rhs.getCenterY();
}

bool comparePCellY(const std::shared_ptr<Cell>& lhs, 
    const std::shared_ptr<Cell>& rhs) {
    return lhs->getCenterY() < rhs->getCenterY();
}
