#include "../include/Vertex.hpp"
#include <iostream>
Vertex::Vertex(Label l, double x, double y) : Point(x, y) {
    label = l;
    weight = 0;
    match = NULL;
    distance = 0;
}

void Vertex::addEdge(Vertex v) {
    edges.push_back(v);
}

//Only have to increment 1 each time
void Vertex::updateWeight() {
    weight = weight + 1;
}

void Vertex::setMatch(Vertex* v) {
    match = v;
}

void Vertex::setDistance(double d) {
    distance = d;
}

void Vertex::createMatch(Vertex v) {
    // match = &v;
    // v.setMatch(this);
}