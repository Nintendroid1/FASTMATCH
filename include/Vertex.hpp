#ifndef VERTEX
#define VERTEX

#include <iostream>
#include <stdio.h>
#include <vector>
#include "Point.hpp"
using namespace std;

/*
* Vertex is a subclass of Point
*/
enum Label {A, B};

class Vertex : public Point {
    private:
        Label label;
        vector<Vertex> edges;
    
    public:
        Vertex(Label l, double x, double y);
        Label getLabel() {return label;}
        vector<Vertex> getEdges() {return edges;}
        void addEdge(Vertex v);
};
#endif