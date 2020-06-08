#include "catch.hpp"
#include "../include/Grid.hpp"

TEST_CASE( "Grid generated", "[grid]" ) {
    Grid g(2.0, 0.01);

    double l = ((2.0*0.01)/(6*sqrt(2)));

    REQUIRE( g.getDelta() == 2.0 );
    REQUIRE( g.getSideLength() == l );
}

//TODO populateCells