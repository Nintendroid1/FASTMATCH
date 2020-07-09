#include "../include/Point.hpp"
/*
 * Parent class that holds the x and y coordinate
 */
Point::Point(double tempX, double tempY) {
    x = tempX;
    y = tempY;
 }

//Returns true if this point has a lesser x value
bool Point::compareX(Point const & p1, Point const & p2) {
    return p1.getX() < p2.getX();
}

//Returns true if this point has a lesser y value
bool Point::compareY(Point const & p1, Point const & p2) {
    return p1.getY() < p2.getY();
}

//Returns euclidean distance between two points
double calcDist(Point const & p1, Point const & p2) {
    return sqrt(pow((p1.getX() - p2.getX()), 2) 
            + pow((p1.getY() - p2.getY()), 2));
}