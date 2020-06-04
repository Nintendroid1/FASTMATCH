#ifndef CELL
#define CELL

#include <stdio.h>
#include <vector>
//#include <bits/stdc++.h> 

#include "Vertex.hpp"

using namespace std;

/*
* Contains vertices from both class A and B
* Contained in a Grid
*/

class Cell{
    private:
        vector<Vertex> vertices;
        vector<Vertex> vertexA;
        vector<Vertex> vertexB;
        int cellIndex;

    public:
        Cell(int i);
        
        //Add vertex to overall list and based on specific class
        void addVertex(Vertex v);
            
        //Cell is active if (A \union B) \intersect Cell is nonempty
        bool isActive(vector<Vertex> allVertices);

        vector<Vertex> getAllVertices() {return vertices;}
        vector<Vertex> getVertexA() {return vertexA;}
        vector<Vertex> getVertexB() {return vertexB;}
        int getCellIndex() {return cellIndex;}
};
#endif