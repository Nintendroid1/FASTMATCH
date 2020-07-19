// Copyright 2020, Nathaniel Salazar, All rights reserved

#ifndef INCLUDE_VERTEX_H_
#define INCLUDE_VERTEX_H_

#include <stdio.h>
#include <math.h>

#include <algorithm>
#include <iostream>

#include "Label.h"

/*
*  This implementation assumes a 2-D representation
*  Can be extended to higher dimension.
*  Part of Cell
*/
struct Vertex {
    Label label;
    double x;
    double y;
};

double calcVertexDist(Vertex const & lhs, Vertex const & rhs);
bool compareVertexX(Vertex const& lhs, Vertex const& rhs);
bool compareVertexY(Vertex const& lhs, Vertex const& rhs);

#endif  // INCLUDE_VERTEX_H_
