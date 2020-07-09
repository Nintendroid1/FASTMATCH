#ifndef MATCH
#define MATCH

#define NIL 0 
#define INF DBL_MAX 

#include <iostream>
#include <stdio.h>
#include <vector>
#include <float.h>
#include <queue> 

#include "GridGen.hpp"

using namespace std;

//https://www.geeksforgeeks.org/hopcroft-karp-algorithm-for-maximum-matching-set-2-implementation/
class Match {
    private:
        vector<Vertex> vertices;
        double shortestDist;
    public:
        Match(vector<Vertex> vs);
        bool bfs();
        bool dfs(Vertex v);

};

#endif