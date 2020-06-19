#include "catch.hpp"
#include "../include/BinaryTree.hpp"

TEST_CASE( "Binary Tree generated", "[binarytree]" ) {
    BinaryTree<int> tree;

	tree.insert(5);
	tree.insert(4);
	tree.insert(7);
	tree.insert(10);
	tree.insert(1);
	tree.insert(2);

    REQUIRE( tree.size() == 6 );
    REQUIRE( tree.search(5) == true );
    REQUIRE( tree.search(17) == false );

}

TEST_CASE( "Binary Tree from data", "[binarytree]" ) {
    BinaryTree<int> tree;
	std::vector<int> d;

    for (int i=1; i<8; ++i) {
        d.push_back(i);
    }
	tree.buildTree(d);
	// tree.printPreOrder(); //4, 2, 1, 3, 6, 5, 7

    REQUIRE( tree.size() == 7 );
    REQUIRE( tree.search(5) == true );
    REQUIRE( tree.search(17) == false );

    d.clear();
}