#include "../include/exp-main.hpp"

/*
* Main runner for developing test cases and running Hopcroft-Karp Algorithm
* and the new FASTMATCH algorithm  
*/
//TODO Boost options
int main(int argc, char *argv[]) {
    //Default: unit square, 0.01 error with 100 points
    double delta = 1.0;
    double epsilon = 0.01;
    double n = 100;

    //Normal Distribution
    int distNum = 1;

    //User specify
    if(argc == 3) { 
        delta = atof(argv[1]);
        n = atof(argv[2]);
        distNum = atoi(argv[3]);
    }
    else if(argc > 4){
        cout << "Usage: ./exp_gen [delta] [n] [dist]" << endl;
        return 0;
    }

    cout << "Cell Side Length: " << (epsilon*delta)/(6*sqrt(2)) << endl;
    genRandPoints(delta, n, distNum);

    return 0;
}