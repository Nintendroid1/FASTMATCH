#include "catch.hpp"
#include "../include/Match.hpp"

TEST_CASE( "BFS", "[match]" ) {
    Vertex v1(A, 0.0, 0.0);
    Vertex v2(B, 2.0, 2.0);
    Vertex v3(B, 2.0, -2.0);
    Vertex v4(A, 4.0, 4.0);
    Vertex v5(A, 4.0, 2.0);
    Vertex v6(A, 4.0, -2.0);
    Vertex v7(A, 4.0, -4.0);

    //Edges
    //(v1,v2), (v1, v3), (v2, v4), (v2, v5), (v3, v6), (v3, v7)
    v1.addEdge(v2);
    v1.addEdge(v3);
    v2.addEdge(v4);
    v2.addEdge(v5);
    v3.addEdge(v6);
    v3.addEdge(v7);
    
    // cout << "(" << v1.getEdges()[0].getX() << ", " << v1.getEdges()[0].getY() << ")" << endl;
    // cout << "(" << v2.getEdges()[0].getX() << ", " << v2.getEdges()[0].getY() << ")" << endl;
    // cout << "(" << v3.getEdges()[0].getX() << ", " << v3.getEdges()[0].getY() << ")" << endl;

    vector<Vertex> vertices;
    vertices.push_back(v1);
    vertices.push_back(v2);
    vertices.push_back(v3);
    vertices.push_back(v4);
    vertices.push_back(v5);
    vertices.push_back(v6);
    vertices.push_back(v7);

    Match m(vertices);

    REQUIRE( m.bfs() == true );
}

TEST_CASE( "DFS", "[match]" ) {
    Vertex v1(A, 0.0, 0.0);
    Vertex v2(B, 2.0, 2.0);
    Vertex v3(B, 2.0, -2.0);
    Vertex v4(A, 4.0, 4.0);
    Vertex v5(A, 4.0, 2.0);
    Vertex v6(A, 4.0, -2.0);
    Vertex v7(A, 4.0, -4.0);

    //Edges
    //(v1,v2), (v1, v3), (v2, v4), (v2, v5), (v3, v6), (v3, v7)
    v1.addEdge(v2);
    v1.addEdge(v3);
    v2.addEdge(v4);
    v2.addEdge(v5);
    v3.addEdge(v6);
    v3.addEdge(v7);
    
    // cout << "(" << v1.getEdges()[0].getX() << ", " << v1.getEdges()[0].getY() << ")" << endl;
    // cout << "(" << v2.getEdges()[0].getX() << ", " << v2.getEdges()[0].getY() << ")" << endl;
    // cout << "(" << v3.getEdges()[0].getX() << ", " << v3.getEdges()[0].getY() << ")" << endl;

    vector<Vertex> vertices;
    vertices.push_back(v1);
    vertices.push_back(v2);
    vertices.push_back(v3);
    vertices.push_back(v4);
    vertices.push_back(v5);
    vertices.push_back(v6);
    vertices.push_back(v7);

    Match m(vertices);
    m.bfs();
    REQUIRE( m.dfs(&v1) == true );
}

TEST_CASE( "BFS False", "[match]" ) {
    Vertex v1(A, 0.0, 0.0);
    Vertex v2(B, 2.0, 2.0);

    vector<Vertex> vertices;
    vertices.push_back(v1);
    vertices.push_back(v2);

    Match m(vertices);
    REQUIRE(m.bfs() == false );
}

TEST_CASE( "DFS False", "[match]" ) {
    Vertex v1(A, 0.0, 0.0);
    Vertex v2(B, 2.0, 2.0);

    vector<Vertex> vertices;
    vertices.push_back(v1);
    vertices.push_back(v2);

    Match m(vertices);
    m.bfs();
    REQUIRE(m.dfs(&v1) == false );
}

TEST_CASE( "HK", "[match]" ) {
    Vertex v1(A, 0.5, 0.0);
    Vertex v2(B, 2.0, 2.0);

    v1.addEdge(v2);

    vector<Vertex> vertices;
    vertices.push_back(v1);
    vertices.push_back(v2);

    Match m(vertices);
    m.HK();

    REQUIRE(m.getHKResult()[0].isFree() == false);
    REQUIRE(m.getHKResult()[0].getMatch().getX() == v2.getX() );
    REQUIRE(m.getHKResult()[0].getMatch().getY() == v2.getY() );
    REQUIRE(m.getHKResult()[0].getMatch().getLabel() == v2.getLabel() );
}