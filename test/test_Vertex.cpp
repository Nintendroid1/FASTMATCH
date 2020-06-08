#include "catch.hpp"
#include "../include/Vertex.hpp"

TEST_CASE( "Vertex generated", "[vertex]" ) {
    Vertex v1(A, 2.0, 1.0);

    REQUIRE( v1.getX() == 2.0 );
    REQUIRE( v1.getY() == 1.0 );
    REQUIRE( v1.getLabel() == A );
    REQUIRE( v1.getWeight() == 0 );

}

TEST_CASE( "Update weight to Vertex", "[vertex]" ) {
    Vertex v1(A, 2.0, 1.0);
    REQUIRE( v1.getWeight() == 0 );

    v1.updateWeight();
    REQUIRE( v1.getWeight() == 1 );
}

TEST_CASE( "Add Edge to Vertex", "[vertex]" ) {
    Vertex v1(A, 2.0, 1.0);
    Vertex v2(B, 3.0, 1.4);
    v1.addEdge(v2);

    REQUIRE( v1.getEdges()[0].getX() == 3.0 );
    REQUIRE( v1.getEdges()[0].getY() == 1.4 );
    REQUIRE( v1.getEdges()[0].getLabel() == B );
    REQUIRE( v1.getEdges()[0].getWeight() == 0 );

}