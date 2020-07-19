// Copyright 2020, Nathaniel Salazar, All rights reserved

#include "../include/Vertex.hpp"

// Returns the Euclidean between two points
double calcVertexDist(Vertex const & lhs, Vertex const & rhs) {
    return sqrt(pow((lhs.x - rhs.x), 2)
            + pow((lhs.y - rhs.y), 2));
}

bool compareVertexX(Vertex const& lhs, Vertex const& rhs) {
    return lhs.x < rhs.x;
}

bool compareVertexY(Vertex const& lhs, Vertex const& rhs) {
    return lhs.y < rhs.y;
}
