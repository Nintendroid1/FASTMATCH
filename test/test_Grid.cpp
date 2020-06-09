#include "catch.hpp"
#include "../include/Grid.hpp"
#include <vector>

TEST_CASE( "Grid generated", "[grid]" ) {
    Grid g(2.0, 0.01);

    double l = ((2.0*0.01)/(6*sqrt(2)));

    REQUIRE( g.getDelta() == 2.0 );
    REQUIRE( g.getSideLength() == l );
}

TEST_CASE( "Grid populateCells", "[grid]" ) {
    Grid g(4.0, 0.01);

    double l = ((4.0*0.01)/(6*sqrt(2)));
    vector<Vertex> vs;
    Vertex v1(A, 2.0, 1.0);
    Vertex v2(B, 3.0, 1.4);
    vs.push_back(v1);
    vs.push_back(v2);

    g.populateCells(vs);

    double centerX1 = -4.0 + g.getCells()[0].getRowIndex() * l + l/2;
    double centerY1 = -4.0 + g.getCells()[0].getColIndex() * l + l/2;
    double centerX2 = -4.0 + g.getCells()[1].getRowIndex() * l + l/2;
    double centerY2 = -4.0 + g.getCells()[1].getColIndex() * l + l/2;
    REQUIRE( g.getCells()[0].getVertexA().getX() ==  centerX1);
    REQUIRE( g.getCells()[0].getVertexA().getY() ==  centerY1);
    REQUIRE( g.getCells()[1].getVertexA().getX() ==  centerX2);
    REQUIRE( g.getCells()[1].getVertexA().getY() ==  centerY2);

}