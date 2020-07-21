#include "catch.hpp"
#include "../include/Cell.hpp"

TEST_CASE( "Cell generated", "[cell]" ) {
    Cell c;
    REQUIRE( c.getWeightA() == 0);
    REQUIRE( c.getWeightB() == 0);
    REQUIRE( c.getCapacity() == 0);
    REQUIRE( c.getStatus() == NONE );
    REQUIRE( c.getDistance() == 0.0);
    REQUIRE( c.isFree() == true);
}

TEST_CASE( "Cell center points generate", "[cell]") {
    Cell c;
    c.createCenter(0, 3, -1.0, -1.0, 2.0);

    REQUIRE( c.getCenterX() == 0 );
    REQUIRE( c.getCenterY() == 6 );
        
    REQUIRE( c.getCenterX() == 0 );
    REQUIRE( c.getCenterY() == 6 );
}

TEST_CASE( "Cell addVertex A", "[cell]") {
    Cell c;
    c.createCenter(0, 3, -1.0, -1.0, 2.0);

    c.addVertex(A);

    REQUIRE( c.getStatus() == ASET );
    REQUIRE( c.getWeightA() == 1 );

    c.addVertex(B);
    REQUIRE( c.getStatus() == ALL );
}

TEST_CASE( "Cell addVertex B", "[cell]") {
    Cell c;
    c.createCenter(0, 3, -1.0, -1.0, 2.0);
    c.addVertex(B);

    REQUIRE( c.getStatus() == BSET );
    REQUIRE( c.getWeightB() == 1 );

    c.addVertex(A);
    REQUIRE( c.getStatus() == ALL );
}

TEST_CASE( "Compare Cells", "[cell]" ) {
    Cell c1;
    c1.createCenter(0, 3, -1.0, -1.0, 2.0);

    Cell c2;
    c2.createCenter(3, 0, -1.0, -1.0, 2.0);

    std::vector<Cell> cells;
    cells.push_back(c1);
    cells.push_back(c2);

    sort(cells.begin(), cells.end(), compareCellX);
    REQUIRE( cells[0].getCenterX() == c1.getCenterX() );
    REQUIRE( cells[1].getCenterX() == c2.getCenterX() );

    sort(cells.begin(), cells.end(), compareCellY);
    REQUIRE( cells[0].getCenterY() == c2.getCenterY() );
    REQUIRE( cells[1].getCenterY() == c1.getCenterY() );

    cells.clear();
}

TEST_CASE( "Cell matches", "[cell]" ) {
    std::shared_ptr<Cell> c1 =  std::make_shared<Cell>();
    c1->createCenter(0, 3, -1.0, -1.0, 2.0);

    std::shared_ptr<Cell> c2 =  std::make_shared<Cell>();
    c2->createCenter(3, 0, -1.0, -1.0, 2.0);

    c1->setMatch(std::weak_ptr<Cell>(c2));
    c2->setMatch(std::weak_ptr<Cell>(c1));

    std::shared_ptr<Cell> c1Match = c1->getMatch().lock();
    std::shared_ptr<Cell> c2Match = c2->getMatch().lock();

    REQUIRE( c1Match->getCenterX() == c2->getCenterX());
    REQUIRE( c1Match->getCenterY() == c2->getCenterY());
    REQUIRE( c1->isFree() == false);
    
    REQUIRE( c2Match->getCenterX() == c1->getCenterX());
    REQUIRE( c2Match->getCenterY() == c1->getCenterY());
    REQUIRE( c2->isFree() == false);

}

TEST_CASE( "Cell edges", "[cell]" ) {
    std::shared_ptr<Cell> c1 =  std::make_shared<Cell>();
    c1->createCenter(0, 3, -1.0, -1.0, 2.0);

    std::shared_ptr<Cell> c2 =  std::make_shared<Cell>();
    c2->createCenter(3, 0, -1.0, -1.0, 2.0);

    c1->formEdgeA(std::weak_ptr<Cell>(c2));
    c2->formEdgeB(std::weak_ptr<Cell>(c1));

    REQUIRE(c1->getEdgesToA().size() == 1);
    REQUIRE(c1->getEdgesToB().size() == 0);
    REQUIRE(c2->getEdgesToA().size() == 0);
    REQUIRE(c2->getEdgesToB().size() == 1);

    std::shared_ptr<Cell> c1Edge = c1->getEdgesToA()[0].lock();
    std::shared_ptr<Cell> c2Edge = c2->getEdgesToB()[0].lock();

    REQUIRE( c1Edge->getCenterX() == c2->getCenterX());
    REQUIRE( c1Edge->getCenterY() == c2->getCenterY());
    
    REQUIRE( c2Edge->getCenterX() == c1->getCenterX());
    REQUIRE( c2Edge->getCenterY() == c1->getCenterY());

}

TEST_CASE( "Cell ==", "[cell]" ) {
    std::shared_ptr<Cell> c1 =  std::make_shared<Cell>();
    c1->createCenter(0, 3, -1.0, -1.0, 2.0);

    std::shared_ptr<Cell> c2 =  std::make_shared<Cell>();
    c2->createCenter(3, 0, -1.0, -1.0, 2.0);

    std::vector<std::weak_ptr<Cell>> P;
    P.push_back(std::weak_ptr<Cell>(c1));

    REQUIRE( std::find(P.begin(), P.end(), c1) != P.end());
    REQUIRE( std::find(P.begin(), P.end(), c2) == P.end());

}
