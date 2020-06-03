#include "../include/Point.hpp"
/*
 * Parent class that holds the x and y coordinate
 */
Point::Point(double tempX, double tempY) {
     x = tempX;
     y = tempY;
 }

//Returns true if this point has a greater x value
bool Point::compareX(Point p2) {
    return x >= p2.getX();
}

//Returns true if this point has a greater x value
bool Point::compareY(Point p2) {
    return y >= p2.getY();
}