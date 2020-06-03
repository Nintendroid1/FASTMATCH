#ifndef GRIDGEN
#define GRIDGEN

#include <iostream>
#include <stdio.h>
#include <vector>
#include "Point.hpp"
using namespace std;

class GridGen {
    private:
        double epsilon;
        //Calculate range of [alpha/n, alpha]
        vector<double> alphaRange;
        
        //alpha => n-approximation of the bottleneck distance
        void calculateAlpha();
    public:
        //G be a grid on the bounding square S
        GridGen(double e, vector<double> ar);

        //Iterate through possible delta values from alphaRange
        //TODO: Return type?
        void generate();
};

#endif
