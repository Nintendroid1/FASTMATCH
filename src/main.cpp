#include "../include/main.hpp"

/*
* Main runner for developing test cases and running Hopcroft-Karp Algorithm
* and the new FASTMATCH algorithm  
*/
int main(int argc, char *argv[]) {
    Vertex p1(A, 3.0, 4.0); 
    Vertex p2(B, 2.0, 5.0);

    cout << p1.compareX(p2) << endl;
    cout << p1.compareY(p2) << endl;

    cout << p2.getLabel() << endl;
}