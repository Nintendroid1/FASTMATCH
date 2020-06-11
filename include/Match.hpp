#ifndef MATCH
#define MATCH

#define NIL 0 
#define INF DBL_MAX 

#include <iostream>
#include <stdio.h>
#include <vector>
#include <float.h>
#include "GridGen.hpp"

using namespace std;

//https://www.geeksforgeeks.org/hopcroft-karp-algorithm-for-maximum-matching-set-2-implementation/
class Match {
    private:
        //v=> Class A, u=> Class B
        //Stores pair of u if v is matched, NIL otherwise
        vector<Vertex> pairA;
        vector<Vertex> pairB;
        vector<Vertex> dist;
        
        //Size of class A
        int nA;
        //Size of class B
        int nB; 

        bool bfs();
        bool dfs(Vertex v);

}

#endif