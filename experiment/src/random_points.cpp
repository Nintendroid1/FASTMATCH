// Copyright 2020, Nathaniel Salazar, All rights reserved

#include "../include/random_points.hpp"

// Generate points in the bounding square using normal distribution
// num = total number of points to generate
void genRandPoints(double boundary, int n, int distNum) {
    // 2 delta
    double lower_bound = -boundary;
    double upper_bound = boundary;

    char buffer[100];
    snprintf(buffer, sizeof(buffer), "data/nd_%.2f_%d.txt", delta, n);
    ofstream dataFile(buffer);
    dataFile << "Normal Distribution with Delta = ";
    dataFile << delta << " with " << n << " points." << endl;

    // https://en.cppreference.com/w/cpp/numeric/random
    random_device rd{};
    mt19937 gen{rd()};

    normal_distribution<double> dist;
    // TODO(Nintendroid1): Different distributions
    // switch(distNum) {
    //     case 0:
    //         uniform_real_distribution<double> dist;
    //         break;
    //     case 1:
    //         normal_distribution<double> dist;
    //         break;
    // }

    // Generate n points within bounding square
    // Equal points from both classes
    for (int i = 0; i < n; i++) {
        double x = 0.0;
        double y = 0.0;
        while (true) {
            x = dist(gen);
            y = dist(gen);

            if (x < lower_bound || x > upper_bound ||
                y < lower_bound || y > upper_bound) {
                    break;
                }
        }

        if (i % 2 == 0) {
            dataFile << "A: " << x << " " << y << endl;
        } else {
            dataFile << "B: " << x << " " << y << endl;
        }
    }

    dataFile.close();
}
