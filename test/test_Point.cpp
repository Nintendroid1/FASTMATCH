#include "catch.hpp"
#include "../include/Point.hpp"

TEST_CASE( "Point generated", "[point]" ) {
    Point p1(0.5, 1.0);
    REQUIRE( p1.getX() == 0.5 );
    REQUIRE( p1.getY() == 1.0 );
}

TEST_CASE( "Compare Points", "[point]" ) {
    Point p1(0.5, 1.0);
    Point p2(-3.0, 2.0);
    
    REQUIRE( p1.getX() == 0.5 );
    REQUIRE( p1.getY() == 1.0 );

    REQUIRE( p2.getX() == -3.0 );
    REQUIRE( p2.getY() == 2.0 );

    REQUIRE( p1.compareX(p2) == true );
    REQUIRE( p1.compareY(p2) == false);
}