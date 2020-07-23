// Copyright 2020, Nathaniel Salazar, All rights reserved

#ifndef INCLUDE_MATCH_HPP_
#define INCLUDE_MATCH_HPP_

#define NIL 0
#define INF DBL_MAX

#include <stdio.h>
#include <float.h>

#include <iostream>
#include <vector>
#include <queue>

#include "Grid.hpp"

// https://www.geeksforgeeks.org/hopcroft-karp-algorithm-for-maximum-matching-set-2-implementation/
class Match {
 private:
    std::vector<std::shared_ptr<Cell>> cells;
    double shortestDist;

    std::vector<std::weak_ptr<Cell>> P;  // Path = <b = v_1>
    std::shared_ptr<Cell> v_1;  // Initial start in modDFS stored in P
    std::vector<std::tuple<std::weak_ptr<Cell>, bool>> visited;
    void createMatch(std::shared_ptr<Cell> v, std::shared_ptr<Cell> u);
    void deleteEdges();
 public:
    explicit Match(std::vector<std::shared_ptr<Cell>> cs);

    void modHK();
    void modifiedHK();
    bool bfs();
    bool dfs(std::shared_ptr<Cell> c);

    bool modDFS(std::weak_ptr<Cell> v_k);

    // Getters
    std::vector<std::shared_ptr<Cell>> getModHKResult() {return cells;}
};

#endif  // INCLUDE_MATCH_HPP_
