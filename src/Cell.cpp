#include "../include/Cell.hpp"

Cell::Cell(int i) {
    cellIndex = i;
}

//Add vertex to overall list and based on specific class
void Cell::addVertex(Vertex v) {
    vertices.push_back(v);
    if(v.getLabel() == A) {
        vertexA.push_back(v);
    }
    else { //v.label == Label.B
        vertexB.push_back(v);
    }
}

//Cell is active if (A \union B) \intersect Cell is nonempty
//TODO set_intersection?
bool Cell::isActive(vector<Vertex> allVertices) {
    for(int i=0; i < vertices.size(); i++) {
        for(int j=0; j < allVertices.size(); j++) {
            if(vertices[i].getX() == allVertices[i].getX() &&
                vertices[i].getY() == allVertices[i].getY() &&
                vertices[i].getLabel() == allVertices[i].getLabel()) {
                    return true;
                }
        }
    }
    return false;
}
