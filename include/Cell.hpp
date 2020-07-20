// Copyright 2020, Nathaniel Salazar, All rights reserved

#ifndef INCLUDE_CELL_HPP_
#define INCLUDE_CELL_HPP_

#include <stdio.h>
#include <math.h>

#include <algorithm>
#include <vector>
#include <iostream>
#include <memory>

#include "Vertex.hpp"
#include "Status.hpp"

/*
*  Hold the two center vertices and their 
*  edges to other cells.
*  Part of Grid
*/
class Cell {
 private:
    double centerX;
    double centerY;

    std::vector<std::weak_ptr<Cell>> edgesToA;  // Cells with Label B
    std::vector<std::weak_ptr<Cell>> edgesToB;  // Cells with Label A

    int weightA;  //# of Vertices in Cell with Label A
    int weightB;  //# of Vertices in Cell with Label B
    double capacity;

    Status status;

    std::weak_ptr<Cell> match;
    bool free;
    double distance;

 public:
    Cell();
    ~Cell();
    void createCenter(int row, int col,
        double minX, double minY, double cellLength);
    void addVertex(Label l);
    void formEdgeA(std::weak_ptr<Cell> vB);
    void formEdgeB(std::weak_ptr<Cell> vA);
    void setMatch(std::weak_ptr<Cell> c);
    void setDistance(double d);

    // Getters
    double getCenterX() const {return centerX;}
    double getCenterY() const {return centerY;}

    std::vector<std::weak_ptr<Cell>> getEdgesToA() {return edgesToA;}
    std::vector<std::weak_ptr<Cell>> getEdgesToB() {return edgesToB;}

    int getWeightA() {return weightA;}
    int getWeightB() {return weightB;}
    double getCapacity() {return capacity;}

    Status getStatus() {return status;}

    std::weak_ptr<Cell> getMatch() {return match;}
    bool isFree() {return free;}
    double getDistance() {return distance;}
};

bool compareCellX(Cell const& lhs, Cell const& rhs);
bool compareCellY(Cell const& lhs, Cell const& rhs);
bool comparePCellY(const std::shared_ptr<Cell>& lhs, 
     const std::shared_ptr<Cell>& rhs);

#endif  // INCLUDE_CELL_HPP_
