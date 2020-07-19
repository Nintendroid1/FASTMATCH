// Copyright 2020, Nathaniel Salazar, All rights reserved

#ifndef INCLUDE_GRID_HPP_
#define INCLUDE_GRID_HPP_

#include <stdio.h>
#include <math.h>

#include <algorithm>
#include <vector>
#include <iostream>
#include <memory>

#include "Cell.hpp"

/*
*  Hold the two center vertices and their 
*  edges to other cells.
*  Part of Grid
*/
class Grid {
 private:
   std::vector<Vertex> verticesX;  // Vertices sorted by X
   std::vector<Vertex> verticesY;  // Vertices sorted by Y

   std::vector<std::shared_ptr<Cell>> cellsX;  // Cells sorted by X
   std::vector<std::shared_ptr<Cell>> cellsY;  // Cells sorted by Y
   
   double startX;
   double startY;
   double endX;
   double endY;
   
   double sideLength;  // Sidelength of each cell
   double delta;

 public:
   Grid(double d, double epsilon, std::vector<Vertex> aV);
   ~Grid();

   void determineBoundingSquare();
   void populateCells();
   void formEdges();

   int bsCellX(int l, int r, double x);
   int bsCellY(int l, int r, double y);
   // Getters
   std::vector<std::shared_ptr<Cell>> getCells() const {return cellsX;}

   double getStartX() const {return startX;}
   double getStartY() const {return startY;}
   double getEndX() const {return endX;}
   double getEndY() const {return endY;}

   double getSideLength() const {return sideLength;}
   double getDelta() const {return delta;}
};

Grid generateGrid(double d, double epsilon, std::vector<Vertex> aV);
#endif  // INCLUDE_GRID_HPP_
