#include "include/main.hpp"

/*
* Main runner for running Hopcroft-Karp Algorithm
* and the new FASTMATCH algorithm  
* with test cases generated from experiments
*/
int main(int argc, char *argv[]) {
    if(argc == 3) {
        string fileName = string(argv[2]);
        ifstream inputFile;
        inputFile.open(fileName);

        if (!inputFile) {
            cerr << "Could not open " << fileName << endl;
            return 0;
        } else {
            string data;
            getline(inputFile, data);  //Info header
            vector<Vertex> allVertices;
            while (getline(inputFile, data)) {
                istringstream iss(data);
                string label, xCoor, yCoor;
                iss >> label >> xCoor >> yCoor;

                //Assumes two classes
                if (label == "A:") {
                    allVertices.push_back(Vertex(A, stof(xCoor), stof(yCoor)));
                } else {
                    allVertices.push_back(Vertex(B, stof(xCoor), stof(yCoor)));
                }
            }

            //Create Grid
            double e = 0.01;
            vector<double> ar;
            double d = 0.1;
            ar.push_back(1.0);
            GridGen gg = GridGen(e, ar);
            Grid g = gg.generateG(d, allVertices);
            allVertices.clear();

            if (string(argv[1]) == "HK") {
                
            } else if (string(argv[1]) == "FAST") {
                //TODO(me): FASTMATCH implementation
            }
        }
        inputFile.close();
    } else {
        cout << "Usage: ./fastmatch [HK | FAST] [DATAFILE]" << endl;
    }
    return 0;
}