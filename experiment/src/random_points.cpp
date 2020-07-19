// Copyright 2020, Nathaniel Salazar, All rights reserved

#include "../include/random_points.h"

// Generate points in the bounding square using normal distribution
// num = total number of points to generate
void genRandPoints(double boundary, int n, int distNum) {
    // 2 delta
    double lower_bound = -boundary;
    double upper_bound = boundary;

    char buffer[100];
    snprintf(buffer, sizeof(buffer), "data/nd_%d.txt", n);
    std::ofstream dataFile(buffer);
    dataFile << "Normal Distribution";
    dataFile << " with " << n << " points." << std::endl;

    // https://en.cppreference.com/w/cpp/numeric/random
    std::random_device rd{};
    std::mt19937 gen{rd()};

    std::normal_distribution<double> dist;
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
            dataFile << "A: " << x << " " << y << std::endl;
        } else {
            dataFile << "B: " << x << " " << y << std::endl;
        }
    }

    dataFile.close();
}
