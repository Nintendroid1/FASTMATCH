#ifndef POINT
#define POINT

#include <stdio.h>
#include <algorithm>
using namespace std;

/*
* This implementation assumes a 2-D representation
* Can be extended to higher dimension
*/
class Point {
    private:
        double x;
        double y;
    
    public:
        Point(double tempX, double tempY);
        double getX() const {return x;}
        double getY() const {return y;}
        static bool compareX(Point const & p1, Point const & p2);
        static bool compareY(Point const & p1, Point const & p2);
};
#endif