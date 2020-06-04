#include "../include/Vertex.hpp"

Vertex::Vertex(Label l, double x, double y) : Point(x, y) {
    label = l;
    weight = 0;
}

void Vertex::addEdge(Vertex v) {
    edges.push_back(v);
}

//Only have to increment 1 each time
void Vertex::updateWeight() {
    weight = weight + 1;
}