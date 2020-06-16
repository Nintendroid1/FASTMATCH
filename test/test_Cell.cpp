#include "catch.hpp"
#include "../include/Cell.hpp"

TEST_CASE( "Cell generated", "[cell]" ) {
    Cell c(0, 3, -1.0, -1.0, 2.0);

    REQUIRE( c.getRowIndex() == 0 );
    REQUIRE( c.getColIndex() == 3 );
    REQUIRE( c.getCellLength() == 2.0 );
    REQUIRE( c.getCellStatus() == NONE );
}

TEST_CASE( "Cell center points generate", "[cell]") {
    Cell c(0, 3, -1.0, -1.0, 2.0);
    c.createCenter();

    REQUIRE( c.getVertexA().getLabel() == A );
    REQUIRE( c.getVertexA().getX() == 0 );
    REQUIRE( c.getVertexA().getY() == 6 );
        
    REQUIRE( c.getVertexB().getLabel() == B );
    REQUIRE( c.getVertexB().getX() == 0 );
    REQUIRE( c.getVertexB().getY() == 6 );
}

TEST_CASE( "Cell addVertex A", "[cell]") {
    Cell c(0, 3, -1.0, -1.0, 2.0);
    c.createCenter();
    Vertex vA(A, 2.0, 1.0);
    c.addVertex(vA);

    REQUIRE( c.getVertexA().getLabel() == A );
    REQUIRE( c.getCellStatus() == ASET );
    REQUIRE( c.getVertexA().getWeight() == 1 );

    Vertex vB(B, 1.0, 0.0);
    c.addVertex(vB);
    REQUIRE( c.getCellStatus() == ALL );
}

TEST_CASE( "Cell addVertex B", "[cell]") {
    Cell c(0, 3, -1.0, -1.0, 2.0);
    c.createCenter();
    Vertex vB(B, 2.0, 1.0);
    c.addVertex(vB);

    REQUIRE( c.getVertexB().getLabel() == B );
    REQUIRE( c.getCellStatus() == BSET );
    REQUIRE( c.getVertexB().getWeight() == 1 );

    Vertex vA(A, 1.0, 0.0);
    c.addVertex(vA);
    REQUIRE( c.getCellStatus() == ALL );
}