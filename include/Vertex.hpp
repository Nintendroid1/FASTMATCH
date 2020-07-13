#ifndef VERTEX
#define VERTEX

#include <stdio.h>
#include <vector>
#include "Label.hpp"
#include "Point.hpp"
using namespace std;

/*
* Vertex is a subclass of Point
* Has information of label, edges, and weight
*/

class Vertex : public Point {
    private:
        Label label;
        vector<Vertex> edges;

        //Represents the number of vertices of the same class in a cell
        int weight;

        //Vertex that shares an edge in matching
        vector<Vertex> match;

        //Indicates visited
        double distance;
    
    public:
        Vertex(Label l, double x, double y);
        Label getLabel() {return label;}
        void addEdge(Vertex v);
        void updateWeight();
        void setMatch(Vertex v);
        void setDistance(double d);

        vector<Vertex> getEdges() const {return edges;}
        int getWeight() const {return weight;}
        Vertex getMatch() {return match.front();}
        bool isFree() {return (int)match.size() == 0;}
        double getDistance() {return distance;}
};
#endif