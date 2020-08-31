// Copyright 2020, Nathaniel Salazar, All rights reserved

#ifndef INCLUDE_CELL_HPP_
#define INCLUDE_CELL_HPP_

#include <stdio.h>
#include <math.h>

#include <algorithm>
#include <vector>
#include <iostream>
#include <memory>
#include <tuple>

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

    // src = this, dest = std::weak_ptr<Cell>, visited = bool
    std::vector<std::tuple<std::weak_ptr<Cell>, bool>>
        edgesToA;  // Cells with Label B
    std::vector<std::tuple<std::weak_ptr<Cell>, bool>>
        edgesToB;  // Cells with Label A

    int weightA;  //# of Vertices in Cell with Label A
    int weightB;  //# of Vertices in Cell with Label B
    int capacity;
    int forward;
    int backward; // Flow

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
    void setCapacity(int c);
    void setDistance(double d);
    void setForward(int f);
    void setBackward(int b);

    // Getters
    double getCenterX() const {return centerX;}
    double getCenterY() const {return centerY;}

    std::vector<std::tuple<std::weak_ptr<Cell>, bool>>
        getEdgesToA() {return edgesToA;}
    std::vector<std::tuple<std::weak_ptr<Cell>, bool>>
        getEdgesToB() {return edgesToB;}

    int getWeightA() {return weightA;}
    int getWeightB() {return weightB;}
    int getCapacity() {return capacity;}
    int getForward() {return forward;}
    int getBackward() {return backward;}

    Status getStatus() {return status;}

    std::weak_ptr<Cell> getMatch() {return match;}
    bool isFree() {return free;}
    double getDistance() {return distance;}
};

bool compareCellX(Cell const& lhs, Cell const& rhs);
bool compareCellY(Cell const& lhs, Cell const& rhs);
bool comparePCellX(const std::shared_ptr<Cell>& lhs,
    const std::shared_ptr<Cell>& rhs);
bool comparePCellY(const std::shared_ptr<Cell>& lhs,
     const std::shared_ptr<Cell>& rhs);
bool operator== (const std::weak_ptr<Cell>& plhs,
    const std::weak_ptr<Cell>& prhs);

#endif  // INCLUDE_CELL_HPP_
