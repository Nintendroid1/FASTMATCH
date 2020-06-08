#include "../include/random_points.hpp"

//Generate points in the bounding square using normal distribution
//num = total number of points to generate
void genRandPoints(double delta, int n, int distNum) {
    //2 delta
    double lower_bound = -delta;
    double upper_bound = delta;

    ofstream dataFile;
    char buffer[100];
    snprintf(buffer, sizeof(buffer), "data/nd_%.2f_%d.txt", delta, n);
    dataFile.open(buffer);
    dataFile << "Normal Distribution with Delta = " << delta << " with " << n << " points." << endl;

    //https://en.cppreference.com/w/cpp/numeric/random
    random_device rd{};
    mt19937 gen{rd()};

    normal_distribution<double> dist;
    //TODO Different distributions
    // switch(distNum) {
    //     case 0:
    //         uniform_real_distribution<double> dist;
    //         break;
    //     case 1:
    //         normal_distribution<double> dist;
    //         break;
    // }

    //Generate n points within bounding square */
    for(int i = 0; i < n; i++) {
        double x = 0.0;
        double y = 0.0;
        do {   
            x = dist(gen);
            y = dist(gen);
        }
        while(x < lower_bound || x > upper_bound || y < lower_bound || y > upper_bound);
        dataFile << x << ", " << y << endl; 
    }

    dataFile.close();
}