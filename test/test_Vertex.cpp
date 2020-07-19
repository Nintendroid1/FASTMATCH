#include "catch.hpp"
#include "../include/Vertex.hpp"

TEST_CASE( "Vertex generated", "[vertex]" ) {
    Vertex p1 {A, 0.5, 1.0};
    REQUIRE( p1.label == A );
    REQUIRE( p1.x == 0.5 );
    REQUIRE( p1.y == 1.0 );
}

TEST_CASE( "Compare Vertices", "[vertex]" ) {
    Vertex p1 {A, 0.5, -0.5};
    Vertex p2 {A, -3.0, 2.0};
    Vertex p3 {A, 1.0, 1.0};

    std::vector<Vertex> vertices;
    vertices.push_back(p1);
    vertices.push_back(p2);
    vertices.push_back(p3);

    sort(vertices.begin(), vertices.end(), compareVertexX);
    REQUIRE( vertices[0].x == p2.x );
    REQUIRE( vertices[1].x == p1.x );
    REQUIRE( vertices[2].x == p3.x );

    sort(vertices.begin(), vertices.end(), compareVertexY);
    REQUIRE( vertices[0].y == p1.y );
    REQUIRE( vertices[1].y == p3.y );
    REQUIRE( vertices[2].y == p2.y );

    vertices.clear();
}

TEST_CASE( "Vertex Distance", "[vertex]" ) {
    Vertex v1{A, 1.0, 2.0};
    Vertex v2{B, 2.0, 1.4};
    double dist = sqrt(pow((1.0 - 2.0), 2) 
            + pow((2.0 - 1.4), 2));
    REQUIRE( calcVertexDist(v1, v2) == dist );
}