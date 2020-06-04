#ifndef VERTEX
#define VERTEX

#include <stdio.h>
#include <vector>
#include "Point.hpp"
using namespace std;

/*
* Vertex is a subclass of Point
* Has information of label and edges
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