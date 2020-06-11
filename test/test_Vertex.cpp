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

TEST_CASE( "Vertex Sort", "[vertex]" ) {
    Vertex v1(A, 1.0, 2.0);
    Vertex v2(B, 2.0, 1.4);
    vector<Vertex> vertices;
    vertices.push_back(v1);
    vertices.push_back(v2);

    sort(vertices.begin(), vertices.end(), Point::compareX);
    REQUIRE( vertices[0].getX() == v1.getX() );
    REQUIRE( vertices[1].getX() == v2.getX() );

    sort(vertices.begin(), vertices.end(), Point::compareY);
    REQUIRE( vertices[0].getY() == v2.getY() );
    REQUIRE( vertices[1].getY() == v1.getY() );
}

TEST_CASE( "Vertex Distance", "[vertex]" ) {
    Vertex v1(A, 1.0, 2.0);
    Vertex v2(B, 2.0, 1.4);
    double dist = sqrt(pow((1.0 - 2.0), 2) 
            + pow((2.0 - 1.4), 2));
    REQUIRE( calcDist(v1, v2) == dist );
}