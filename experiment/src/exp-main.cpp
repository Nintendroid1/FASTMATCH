// Copyright 2020, Nathaniel Salazar, All rights reserved

#include "../include/exp-main.h"

/*
*  Main runner for developing test cases and running Hopcroft-Karp Algorithm
*  and the new FASTMATCH algorithm  
*/
// TODO(Nintendroid1): Boost options
int main(int argc, char *argv[]) {
    // Default: unit square, 0.01 error with 100 points
    double boundary = 1.0;
    double epsilon = 0.01;
    double n = 100;

    // Normal Distribution
    int distNum = 1;

    // User specify
    if (argc == 4) {
        boundary = atof(argv[1]);
        n = atof(argv[2]);
        distNum = atoi(argv[3]);

    } else if (argc > 4) {
        std::cout << "Usage: ./exp_gen [boundary] [n] [dist]" << endl;
        return 0;
    }

    std::cout << "Cell Side Length: " << (epsilon*boundary)/(6*sqrt(2)) << endl;
    genRandPoints(boundary, n, distNum);

    return 0;
}
