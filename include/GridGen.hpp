#ifndef GRIDGEN
#define GRIDGEN

#include <iostream>
#include <stdio.h>
#include <vector>
#include "Grid.hpp"
using namespace std;

class GridGen {
    private:
        //Error
        double epsilon;

        //beta_star <= delta <= (1 + epsilon/3)beta_star
        double delta;
        
        //Calculate range of [alpha/n, alpha]
        vector<double> alphaRange;

        //alpha => n-approximation of the bottleneck distance
        void calculateAlpha();
    public:
        //G be a grid on the bounding square S
        GridGen(double e, vector<double> ar); //Multiple delta values to check
        GridGen(double e, double d); //Single delta value to check

        //Iterate through possible delta values from alphaRange to generate G
        void iterateAlpha(vector<Vertex> allVertices);

        Grid generateG(double d, vector<Vertex> allVertices);

        double getEpsilon() {return epsilon;}
        double getDelta() {return delta;}
        vector<double> getAlphaRange() {return alphaRange;}

};

#endif
