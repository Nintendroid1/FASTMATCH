#include "catch.hpp"
#include "../include/Grid.hpp"
#include <vector>

TEST_CASE( "Grid generated", "[grid]" ) {
    vector<Vertex> vs;
    Vertex v1(A, 2.0, 1.0);
    Vertex v2(B, 3.0, 1.4);
    vs.push_back(v1);
    vs.push_back(v2);

    Grid g(2.0, 0.01, vs);

    double l = ((2.0*0.01)/(6*sqrt(2)));

    REQUIRE( g.getDelta() == 2.0 );
    REQUIRE( g.getSideLength() == l );
}

TEST_CASE( "Grid populateCells", "[grid]" ) {

    double l = ((4.0*0.01)/(6*sqrt(2)));
    vector<Vertex> vs;
    Vertex v1(A, 2.0, 1.0);
    Vertex v2(B, 3.0, 1.4);
    vs.push_back(v1);
    vs.push_back(v2);

    Grid g(4.0, 0.01, vs);
    g.determineBoundingSquare();
    g.populateCells();

    double startX = 2.0 - abs(abs(2.0 - 3.0) - abs(1.0 - 2.0))/2;
    double startY = 1.0 - abs(abs(2.0 - 3.0) - abs(1.0 - 2.0))/2;

    double centerX1 = startX + g.getCells()[0].getRowIndex() * l + l/2;
    double centerY1 = startY + g.getCells()[0].getColIndex() * l + l/2;
    double centerX2 = startX + g.getCells()[1].getRowIndex() * l + l/2;
    double centerY2 = startY + g.getCells()[1].getColIndex() * l + l/2;

    REQUIRE( g.getCells()[0].getCenterX() ==  centerX1);
    REQUIRE( g.getCells()[0].getCenterY() ==  centerY1);
    REQUIRE( g.getCells()[1].getCenterX() ==  centerX2);
    REQUIRE( g.getCells()[1].getCenterY() ==  centerY2);

}

TEST_CASE( "Grid formEdges", "[grid]" ) {
    double l = ((4.0*0.01)/(6*sqrt(2)));
    vector<Vertex> vs;
    Vertex v1(A, 2.0, 1.0);
    Vertex v2(B, 3.0, 1.4);
    vs.push_back(v1);
    vs.push_back(v2);

    Grid g(4.0, 0.01, vs);
    g.determineBoundingSquare();
    g.populateCells();


    g.formEdges();
    double startX = 2.0 - abs(abs(2.0 - 3.0) - abs(1.0 - 2.0))/2;
    double startY = 1.0 - abs(abs(2.0 - 3.0) - abs(1.0 - 2.0))/2;

    double centerX1 = startX + g.getCells()[0].getRowIndex() * l + l/2;
    double centerY1 = startY + g.getCells()[0].getColIndex() * l + l/2;
    double centerX2 = startX + g.getCells()[1].getRowIndex() * l + l/2;
    double centerY2 = startY + g.getCells()[1].getColIndex() * l + l/2;


    vector<Vertex> edges1 = g.getCells()[0].getVertexA().getEdges();
    vector<Vertex> edges2 = g.getCells()[1].getVertexB().getEdges();

    REQUIRE( edges1[0].getX() ==  centerX2);
    REQUIRE( edges1[0].getY() ==  centerY2);

    REQUIRE( edges2[0].getX() ==  centerX1);
    REQUIRE( edges2[0].getY() ==  centerY1);

}