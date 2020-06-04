#include "../include/main.hpp"

void print(vector<int> const &input) {
    for (int i=0; i < input.size(); i++) {
        std::cout << input.at(i) << ' ';
    }
    std::cout << '\n';
}

/*
* Main runner for developing test cases and running Hopcroft-Karp Algorithm
* and the new FASTMATCH algorithm  
*/
int main(int argc, char *argv[]) {
    Vertex p1(A, 1.45, 1.0); 
    cout << p1.getX() << endl;

    Cell c(0, 0, 2.0);
    c.addVertex(p1);
    c.addVertex(p1);

    Vertex test = c.getVertexA();

    cout << test.getWeight() << endl;

}