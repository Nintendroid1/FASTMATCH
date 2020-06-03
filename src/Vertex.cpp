#include "../include/Vertex.hpp"

Vertex::Vertex(Label l, double x, double y) : Point(x, y) {
    label = l;
}

void Vertex::addEdge(Vertex v) {
    edges.push_back(v);
}