#include "catch.hpp"
#include "../include/Match.hpp"

TEST_CASE( "Match BFS True", "[match]" ) {
    double l = ((4.0*0.01)/(6*sqrt(2)));
    vector<Vertex> vs;
    Vertex v1(A, 2.0, 1.0);
    Vertex v2(B, 3.0, 1.4);
    vs.push_back(v1);
    vs.push_back(v2);

    Grid g(4.0, 0.01, vs);
    g.determineBoundingSquare();
    g.populateCells();

    // g.formEdges();
    
    Match m(g.getCells());
    REQUIRE(m.bfs() == true );
}

TEST_CASE( "Match BFS False", "[match]" ) {
    double l = ((4.0*0.01)/(6*sqrt(2)));
    vector<Vertex> vs;
    Vertex v1(A, 2.0, 1.0);
    Vertex v2(B, 3.0, 1.4);
    vs.push_back(v1);
    vs.push_back(v2);

    Grid g(4.0, 0.01, vs);
    g.determineBoundingSquare();
    g.populateCells();

    //g.formEdges();
    
    Match m(g.getCells());
    REQUIRE(m.bfs() == false );
}

// TEST_CASE( "Match DFS False", "[match]" ) {
//     double l = ((4.0*0.01)/(6*sqrt(2)));
//     vector<Vertex> vs;
//     Vertex v1(A, 2.0, 1.0);
//     Vertex v2(B, 3.0, 1.4);
//     vs.push_back(v1);
//     vs.push_back(v2);

//     Grid g(4.0, 0.01, vs);
//     g.determineBoundingSquare();
//     g.populateCells();

//     //g.formEdges();
    
//     Match m(g.getCells());
//     REQUIRE(m.dfs() == false );
// }

// TEST_CASE( "HK", "[match]" ) {
//     Vertex v1(A, 0.5, 0.0);
//     Vertex v2(B, 2.0, 2.0);

//     v1.addEdge(v2);

//     vector<Vertex> vertices;
//     vertices.push_back(v1);
//     vertices.push_back(v2);

//     Match m(vertices);
//     m.HK();

//     REQUIRE(m.getHKResult()[0].isFree() == false);
//     REQUIRE(m.getHKResult()[0].getMatch().getX() == v2.getX() );
//     REQUIRE(m.getHKResult()[0].getMatch().getY() == v2.getY() );
//     REQUIRE(m.getHKResult()[0].getMatch().getLabel() == v2.getLabel() );
// }