// Copyright 2020, Nathaniel Salazar, All rights reserved

#include "include/main.hpp"
/*
*  Main runner for running Hopcroft-Karp Algorithm
*  and the new FASTMATCH algorithm  
*  with test cases generated from experiments
*/
int main(int argc, char *argv[]) {
    if (argc == 3) {
        std::string fileName = string(argv[2]);
        std::ifstream inputFile;
        inputFile.open(fileName);

        if (!inputFile) {
            std::cerr << "Could not open " << fileName << std::endl;
            return 0;

        } else {
            string data;
            std::getline(inputFile, data);  // Info header
            vector<Vertex> allVertices;
            while (std::getline(inputFile, data)) {
                std::istringstream iss(data);
                string label, xCoor, yCoor;
                iss >> label >> xCoor >> yCoor;

                // Assumes two classes
                if (label == "A:") {
                    allVertices.push_back(Vertex(A, std::stof(xCoor), std::stof(yCoor)));
                } else {
                    allVertices.push_back(Vertex(B, std::stof(xCoor), std::stof(yCoor)));
                }
            }

            if (string(argv[1]) == "HK") {
                // TODO(Nintendroid1): Hopcroft-Karp implementation
            } else if (string(argv[1]) == "FAST") {
                // TODO(Nintendroid1): FASTMATCH implementation
            }

            double e = 0.01;
            vector<double> ar;
            double d = 0.1;
            ar.push_back(1.0);
            GridGen gg = GridGen(e, ar);
            gg.generateG(d, allVertices);
            allVertices.clear();
        }
        inputFile.close();
    } else {
        std::cout << "Usage: ./fastmatch [HK | FAST] [DATAFILE]" << std::endl;
    }
    return 0;
}
