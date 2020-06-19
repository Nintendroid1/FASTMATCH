#include "catch.hpp"
#include "../include/Point.hpp"
#include <vector>

TEST_CASE( "Point generated", "[point]" ) {
    Point p1(0.5, 1.0);
    REQUIRE( p1.getX() == 0.5 );
    REQUIRE( p1.getY() == 1.0 );
}

TEST_CASE( "Compare Points", "[point]" ) {
    Point p1(0.5, -0.5);
    Point p2(-3.0, 2.0);
    Point p3(1.0, 1.0);

    vector<Point> points;
    points.push_back(p1);
    points.push_back(p2);
    points.push_back(p3);

    sort(points.begin(), points.end(), Point::compareX);
    REQUIRE( points[0].getX() == p2.getX() );
    REQUIRE( points[1].getX() == p1.getX() );
    REQUIRE( points[2].getX() == p3.getX() );

    sort(points.begin(), points.end(), Point::compareY);
    REQUIRE( points[0].getY() == p1.getY() );
    REQUIRE( points[1].getY() == p3.getY() );
    REQUIRE( points[2].getY() == p2.getY() );

    points.clear();
}

TEST_CASE( "Point Distance", "[point]" ) {
    Point p1(-3.0, 2.0);
    Point p2(1.0, 1.0);
    double dist = sqrt(pow((-3.0 - 1.0), 2) 
            + pow((2.0 - 1.0), 2));
    REQUIRE( calcDist(p1, p2) == dist );
}