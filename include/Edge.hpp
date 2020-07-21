// Copyright 2020, Nathaniel Salazar, All rights reserved

#ifndef INCLUDE_EDGE_HPP_
#define INCLUDE_EDGE_HPP_

#include <stdio.h>
#include <math.h>

#include <algorithm>
#include <iostream>
#include <memory>

#include "Cell.hpp"

/*
*  Edge between two cells
*  Indicates if visited
*/
struct Edge {
    std::weak_ptr<Cell> src;
    std::weak_ptr<Cell> dest;
    bool visited;
};

#endif  // INCLUDE_EDGE_HPP_
