// Copyright 2020, Nathaniel Salazar, All rights reserved

#include "include/main.hpp"
/*
*  Main runner for running Hopcroft-Karp Algorithm
*  and the new FASTMATCH algorithm  
*  with test cases generated from experiments
*/
int main(int argc, char *argv[]) {
    if (argc == 3) {
        std::string fileName = std::string(argv[2]);
        std::ifstream inputFile;
        inputFile.open(fileName);

        if (!inputFile) {
            std::cerr << "Could not open " << fileName << std::endl;
            return 0;

        } else {
            std::string data;
            std::getline(inputFile, data);  // Info header
            std::vector<Vertex> allVertices;
            while (std::getline(inputFile, data)) {
                std::istringstream iss(data);
                std::string label, xCoor, yCoor;
                iss >> label >> xCoor >> yCoor;

                // Assumes two classes
                if (label == "A:") {
                    allVertices.push_back(Vertex{A, std::stof(xCoor), std::stof(yCoor)});
                } else {
                    allVertices.push_back(Vertex{B, std::stof(xCoor), std::stof(yCoor)});
                }
            }

            if (std::string(argv[1]) == "HK") {
                // TODO(Nintendroid1): Hopcroft-Karp implementation
            } else if (std::string(argv[1]) == "FAST") {
                // TODO(Nintendroid1): FASTMATCH implementation
            }

            //Create Grid with delta, epsilon, and vertices
            double e = 0.01;
            double d = 1;
            Grid g = generateGrid(d, e, allVertices);
            allVertices.clear();

        }
        inputFile.close();

    } else {
        std::cout << "Usage: ./fastmatch [HK | FAST] [DATAFILE]" << std::endl;
    }
    return 0;
}
