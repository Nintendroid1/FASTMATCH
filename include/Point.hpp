#ifndef POINT
#define POINT

#include <stdio.h>
using namespace std;

/*
* This implementation assumes a 2-D representation
*/
class Point {
    private:
        double x;
        double y;
    
    public:
        Point(double tempX, double tempY);
        double getX(){return x;}
        double getY(){return y;}
        bool compareX(Point p2);
        bool compareY(Point p2);
};
#endif