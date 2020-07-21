  
#include "catch.hpp"
#include "../include/Grid.hpp"

TEST_CASE( "Grid generated", "[grid]" ) {
    std::vector<Vertex> vs;
    Vertex v1{A, 2.0, 1.0};
    Vertex v2{B, 3.0, 1.4};
    vs.push_back(v1);
    vs.push_back(v2);

    Grid g(2.0, 0.01, vs);

    double l = ((2.0*0.01)/(6*sqrt(2)));

    REQUIRE( g.getDelta() == 2.0 );
    REQUIRE( g.getSideLength() == l );

    vs.clear();
}

TEST_CASE( "Grid determine bounding square", "[grid]" ) {
    std::vector<Vertex> vs;
    Vertex v1{A, 2.0, 1.0};
    Vertex v2{B, 3.0, 1.4};
    vs.push_back(v1);
    vs.push_back(v2);

    Grid g(2.0, 0.01, vs);


    g.determineBoundingSquare();
    REQUIRE( g.getStartX() == 2.0 );
    REQUIRE( g.getStartY() == 1.0 );
    REQUIRE( g.getEndX() == 3.0 );
    REQUIRE( g.getEndY() == 2.0 );

    vs.clear();
}

TEST_CASE( "Grid populateCells", "[grid]" ) {

    double l = ((4.0*0.01)/(6*sqrt(2)));
    std::vector<Vertex> vs;
    Vertex v1{A, 2.0, 1.0};
    Vertex v2{B, 3.0, 1.4};
    vs.push_back(v1);
    vs.push_back(v2);

    Grid g(4.0, 0.01, vs);
    g.determineBoundingSquare();
    g.populateCells();

    double startX = 2.0 - abs(abs(2.0 - 3.0) - abs(1.0 - 2.0))/2;
    double startY = 1.0 - abs(abs(2.0 - 3.0) - abs(1.0 - 2.0))/2;

    double centerX1 = startX + 0 * l + l/2;
    double centerY1 = startY + 0 * l + l/2;
    double centerX2 = startX + 212 * l + l/2;
    double centerY2 = startY + 84 * l + l/2;

    REQUIRE( g.getCells()[0]->getCenterX() ==  centerX1);
    REQUIRE( g.getCells()[0]->getCenterY() ==  centerY1);
    REQUIRE( g.getCells()[1]->getCenterX() ==  centerX2);
    REQUIRE( g.getCells()[1]->getCenterY() ==  centerY2);

    vs.clear();
}
TEST_CASE( "Grid formEdges", "[grid]" ) {
    double l = ((4.0*0.01)/(6*sqrt(2)));
    std::vector<Vertex> vs;
    Vertex v1{A, 2.0, 1.0};
    Vertex v2{B, 3.0, 1.4};
    vs.push_back(v1);
    vs.push_back(v2);

    Grid g(4.0, 0.01, vs);
    g.determineBoundingSquare();
    g.populateCells();


    g.formEdges();
    double startX = 2.0 - abs(abs(2.0 - 3.0) - abs(1.0 - 2.0))/2;
    double startY = 1.0 - abs(abs(2.0 - 3.0) - abs(1.0 - 2.0))/2;

    double centerX1 = startX + 0 * l + l/2;
    double centerY1 = startY + 0 * l + l/2;
    double centerX2 = startX + 212 * l + l/2;
    double centerY2 = startY + 84 * l + l/2;

    std::shared_ptr<Cell> edges1 = (std::get<0>(g.getCells()[0]->getEdgesToA()[0])).lock();
    std::shared_ptr<Cell> edges2 = (std::get<0>(g.getCells()[1]->getEdgesToB()[0])).lock();

    REQUIRE( edges1->getCenterX() ==  centerX2);
    REQUIRE( edges1->getCenterY() ==  centerY2);

    REQUIRE( edges2->getCenterX() ==  centerX1);
    REQUIRE( edges2->getCenterY() ==  centerY1);

    vs.clear();
}

