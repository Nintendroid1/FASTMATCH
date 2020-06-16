#include "include/main.hpp"

// void print(vector<int> const &input) {
//     for (int i=0; i < input.size(); i++) {
//         std::cout << input.at(i) << ' ';
//     }
//     std::cout << '\n';
// }

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
        }
        else
        {
            string data;
            getline(inputFile, data);//Info header
            vector<Vertex> allVertices;
            while(getline(inputFile, data)) {
                istringstream iss(data);
                string label, xCoor, yCoor;
                iss >> label >> xCoor >> yCoor;

                //Assumes two classes
                if(label == "A:") {
                    allVertices.push_back(Vertex(A, stof(xCoor), stof(yCoor)));
                }
                else {
                    allVertices.push_back(Vertex(B, stof(xCoor), stof(yCoor)));
                }
            }

            if(string(argv[1]) == "HK") {
            //TODO: Hopcroft-Karp implementation
            }
            else if(string(argv[1]) == "FAST") {
                //TODO: FASTMATCH implementation
            }

            double e = 0.01;
            vector<double> ar;
            double d = 1.0;
            ar.push_back(1.0);
            GridGen gg = GridGen(e, ar);
            gg.generateG(d, allVertices);
            allVertices.clear();
        }
        inputFile.close();
    }
    else {
        cout << "Usage: ./fastmatch [HK | FAST] [DATAFILE]" << endl;
    }
    return 0;
}