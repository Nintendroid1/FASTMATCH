#include "../include/GridGen.hpp"
/*
Based on the epsilon-approximate bottleneck matching algorithm
presented by Lahn and Raghevendra (SoCG 2019)
 */
GridGen::GridGen(double e, vector<double> ar){
    epsilon = e;
    alphaRange = ar;
}
void GridGen::generate() {
    //beta_star <= delta <= (1 + epsilon/3)beta_star
    // for(double delta : alphaRange) {
        //Grid currGraph = new Grid(delta, epsilon);
    // }
    cout << "Test" << endl;
}

//Construct bipartite graph H st point 'b' that is in xi
//Is joined by an edge if it is in the subset of N(xi)
//delta is at least the bottleneck distance, so H will have a perfect matching