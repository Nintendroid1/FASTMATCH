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
 public:
    Match(std::vector<std::shared_ptr<Cell>> cs);
    void modHK();
    bool bfs();
    bool dfs(std::shared_ptr<Cell> c);

    // Getters
    std::vector<std::shared_ptr<Cell>> getModHKResult() {return cells;}
};
#endif  // INCLUDE_MATCH_HPP_
