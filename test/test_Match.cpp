#include "catch.hpp"
#include "../include/Match.hpp"

TEST_CASE( "Match BFS True", "[match]" ) {
    std::vector<Vertex> vs;
    Vertex v1{A, 2.0, 1.0};
    Vertex v2{B, 3.0, 1.4};
    vs.push_back(v1);
    vs.push_back(v2);

    Grid g = generateGrid(4.0, 0.01, vs);

    Match m(g.getCells());
    REQUIRE(m.bfs() == true );
}

TEST_CASE( "Match BFS True 2", "[match]" ) {
    std::shared_ptr<Cell> c1 =  std::make_shared<Cell>();
    c1->createCenter(0, 3, -1.0, -1.0, 2.0);
    c1->addVertex(A);

    std::shared_ptr<Cell> c2 =  std::make_shared<Cell>();
    c2->createCenter(3, 0, -1.0, -1.0, 2.0);
    c2->addVertex(B);

    c1->formEdgeA(std::weak_ptr<Cell>(c2));
    c2->formEdgeB(std::weak_ptr<Cell>(c1));
    
    std::vector<std::shared_ptr<Cell>> cs;
    cs.push_back(c1);
    cs.push_back(c2);
    
    Match m(cs);
    REQUIRE(m.bfs() == true );

    cs.clear();
}

TEST_CASE( "Match BFS False", "[match]" ) {
    std::shared_ptr<Cell> c1 =  std::make_shared<Cell>();
    c1->createCenter(0, 3, -1.0, -1.0, 2.0);

    std::shared_ptr<Cell> c2 =  std::make_shared<Cell>();
    c2->createCenter(3, 0, -1.0, -1.0, 2.0);

    // c1->formEdgeA(std::weak_ptr<Cell>(c2));
    // c2->formEdgeB(std::weak_ptr<Cell>(c1));
    
    std::vector<std::shared_ptr<Cell>> cs;
    cs.push_back(c1);
    cs.push_back(c2);

    Match m(cs);
    REQUIRE(m.bfs() == false );

    cs.clear();
}

TEST_CASE( "Match DFS True", "[match]" ) {
    std::vector<Vertex> vs;
    Vertex v1{A, 2.0, 1.0};
    Vertex v2{B, 3.0, 1.4};
    vs.push_back(v1);
    vs.push_back(v2);

    Grid g = generateGrid(4.0, 0.01, vs);

    Match m(g.getCells());
    m.bfs();
    REQUIRE(m.dfs(g.getCells()[0]) == true );
}

TEST_CASE( "Match DFS True 2", "[match]" ) {
    std::shared_ptr<Cell> c1 =  std::make_shared<Cell>();
    c1->createCenter(0, 3, -1.0, -1.0, 2.0);
    c1->addVertex(A);

    std::shared_ptr<Cell> c2 =  std::make_shared<Cell>();
    c2->createCenter(3, 0, -1.0, -1.0, 2.0);
    c2->addVertex(B);

    c1->formEdgeA(std::weak_ptr<Cell>(c2));
    c2->formEdgeB(std::weak_ptr<Cell>(c1));
    
    std::vector<std::shared_ptr<Cell>> cs;
    cs.push_back(c1);
    cs.push_back(c2);
    
    Match m(cs);
    m.bfs();
    REQUIRE(m.dfs(cs[0]) == true );

    cs.clear();
}

TEST_CASE( "Match DFS False", "[match]" ) {
    std::shared_ptr<Cell> c1 =  std::make_shared<Cell>();
    c1->createCenter(0, 3, -1.0, -1.0, 2.0);

    std::shared_ptr<Cell> c2 =  std::make_shared<Cell>();
    c2->createCenter(3, 0, -1.0, -1.0, 2.0);

    // c1->formEdgeA(std::weak_ptr<Cell>(c2));
    // c2->formEdgeB(std::weak_ptr<Cell>(c1));
    
    std::vector<std::shared_ptr<Cell>> cs;
    cs.push_back(c1);
    cs.push_back(c2);

    Match m(cs);
    m.bfs();
    REQUIRE(m.dfs(cs[0]) == false );

    cs.clear();
}

TEST_CASE( "HK", "[match]" ) {
    std::vector<Vertex> vs;
    Vertex v1{A, 2.0, 1.0};
    Vertex v2{B, 3.0, 1.4};
    vs.push_back(v1);
    vs.push_back(v2);

    Grid g = generateGrid(4.0, 0.01, vs);

    Match m(g.getCells());

    m.modHK();

    REQUIRE(m.getModHKResult()[0]->isFree() == false);

    std::shared_ptr<Cell> cMatch = m.getModHKResult()[0]->getMatch().lock();

    REQUIRE(cMatch->getCenterX() == g.getCells()[1]->getCenterX() );
    REQUIRE(cMatch->getCenterY() == g.getCells()[1]->getCenterY() );
    REQUIRE(cMatch->getWeightB() == g.getCells()[1]->getWeightB() );
    REQUIRE(cMatch->getCapacity() == g.getCells()[1]->getCapacity() );
}

TEST_CASE( "Match modDFS True", "[match]" ) {
    std::vector<Vertex> vs;
    Vertex v1{A, 2.0, 1.0};
    Vertex v2{B, 3.0, 1.4};
    vs.push_back(v1);
    vs.push_back(v2);

    Grid g = generateGrid(4.0, 0.01, vs);

    Match m(g.getCells());
    m.bfs();
    REQUIRE(m.modDFS(g.getCells()[0]) == true );
}

TEST_CASE( "Match modDFS True 2", "[match]" ) {
    std::shared_ptr<Cell> c1 =  std::make_shared<Cell>();
    c1->createCenter(0, 3, -1.0, -1.0, 2.0);
    c1->addVertex(A);

    std::shared_ptr<Cell> c2 =  std::make_shared<Cell>();
    c2->createCenter(3, 0, -1.0, -1.0, 2.0);
    c2->addVertex(B);

    c1->formEdgeA(std::weak_ptr<Cell>(c2));
    c2->formEdgeB(std::weak_ptr<Cell>(c1));
    
    std::vector<std::shared_ptr<Cell>> cs;
    cs.push_back(c1);
    cs.push_back(c2);
    
    Match m(cs);
    m.bfs();
    REQUIRE(m.modDFS(cs[0]) == true );

    cs.clear();
}

TEST_CASE( "modifiedHK", "[match]" ) {
    std::vector<Vertex> vs;
    Vertex v1{A, 2.0, 1.0};
    Vertex v2{B, 3.0, 1.4};
    vs.push_back(v1);
    vs.push_back(v2);

    Grid g = generateGrid(4.0, 0.01, vs);

    Match m(g.getCells());

    m.modifiedHK();

    REQUIRE(m.getModHKResult()[0]->isFree() == false);

    std::shared_ptr<Cell> cMatch = m.getModHKResult()[0]->getMatch().lock();

    REQUIRE(cMatch->getCenterX() == g.getCells()[1]->getCenterX() );
    REQUIRE(cMatch->getCenterY() == g.getCells()[1]->getCenterY() );
    REQUIRE(cMatch->getWeightB() == g.getCells()[1]->getWeightB() );
    REQUIRE(cMatch->getCapacity() == g.getCells()[1]->getCapacity() );
}

TEST_CASE( "Match ffDFS True", "[match]" ) {
    std::vector<Vertex> vs;
    Vertex v1{A, 2.0, 1.0};
    Vertex v2{B, 3.0, 1.4};
    vs.push_back(v1);
    vs.push_back(v2);

    Grid g = generateGrid(4.0, 0.01, vs);

    Match m(g.getCells());
    REQUIRE(m.ffDFS(g.getCells()[0]) == true );
}

TEST_CASE( "Match ffDFS True 2", "[match]" ) {
    std::shared_ptr<Cell> c1 =  std::make_shared<Cell>();
    c1->createCenter(0, 3, -1.0, -1.0, 2.0);
    c1->addVertex(A);

    std::shared_ptr<Cell> c2 =  std::make_shared<Cell>();
    c2->createCenter(3, 0, -1.0, -1.0, 2.0);
    c2->addVertex(B);

    c1->formEdgeA(std::weak_ptr<Cell>(c2));
    c2->formEdgeB(std::weak_ptr<Cell>(c1));
    
    std::vector<std::shared_ptr<Cell>> cs;
    cs.push_back(c1);
    cs.push_back(c2);
    
    Match m(cs);
    REQUIRE(m.ffDFS(cs[0]) == true );

    cs.clear();
}

TEST_CASE( "FordFulk", "[match]" ) {
    std::vector<Vertex> vs;
    Vertex v1{A, 2.0, 1.0};
    Vertex v2{B, 3.0, 1.4};
    vs.push_back(v1);
    vs.push_back(v2);

    Grid g = generateGrid(4.0, 0.01, vs);

    Match m(g.getCells());

    m.FordFulk();

    REQUIRE(m.getModHKResult()[0]->isFree() == false);

    std::shared_ptr<Cell> cMatch = m.getModHKResult()[0]->getMatch().lock();

    REQUIRE(cMatch->getCenterX() == g.getCells()[1]->getCenterX() );
    REQUIRE(cMatch->getCenterY() == g.getCells()[1]->getCenterY() );
    REQUIRE(cMatch->getWeightB() == g.getCells()[1]->getWeightB() );
    REQUIRE(cMatch->getCapacity() == g.getCells()[1]->getCapacity() );
}

TEST_CASE( "Augment Flow", "[match]" ) {
    std::shared_ptr<Cell> c1 =  std::make_shared<Cell>();
    c1->createCenter(0, 3, -1.0, -1.0, 2.0);
    for(int i=0; i<10; i++)
        c1->addVertex(A);

    std::shared_ptr<Cell> c2 =  std::make_shared<Cell>();
    c2->createCenter(3, 0, -1.0, -1.0, 2.0);
    for(int i=0; i<7; i++)
        c2->addVertex(B);

    c1->setForward(4);
    c1->setBackward(3);

    std::vector<std::shared_ptr<Cell>> cs;
    cs.push_back(c1);
    cs.push_back(c2);
    
    Match m(cs);

    int bn = 3;
    m.augmentFlow(c1, c2, bn);

    REQUIRE(c1->getForward() == 7);
    REQUIRE(c1->getBackward() == 0);

    cs.clear();
}