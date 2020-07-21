// Copyright 2020, Nathaniel Salazar, All rights reserved

#include "../include/Match.hpp"

Match::Match(std::vector<std::shared_ptr<Cell>> cs) {
    cells = cs;
}

// Modified Hopcroft-Karp
void Match::modHK() {
    while (bfs()) {
        for (int i = 0; i < static_cast<int>(cells.size()); i++) {
            std::shared_ptr<Cell> c = cells[i];

            // Split by class
            if (c->isFree()) {
                dfs(c);
            }
        }
    }
}
// Returns true if there is an augmenting path, else returns
// false
bool Match::bfs() {
    std::queue<std::weak_ptr<Cell>> Q;

    // First layer of vertices (set distance as 0)
    for (int i=0; i < static_cast<int>(cells.size()); i++) {
        std::shared_ptr<Cell> v = cells[i];

        // If this is a free vertex
        // with label A, add it to queue
        if (v->isFree() && v->getStatus() == ASET) {
            // v is not matched
            Q.push(std::weak_ptr<Cell>(v));
            v->setDistance(0);

        } else {
            // Else set distance as infinite so that this vertex
            // is considered next time
            v->setDistance(INF);
        }
    }
    // Initialize distance to NIL as infinite
    shortestDist = INF;

    // Q is going to contain vertices of left side only.
    while (!Q.empty()) {
        // Dequeue a vertex
        std::shared_ptr<Cell> v = Q.front().lock();
        Q.pop();

        // If this node is not NIL and can provide a shorter path to NIL
        if (v->getDistance() < shortestDist) {
            std::vector<std::weak_ptr<Cell>> edges = v->getEdgesToA();

            // Get all adjacent vertices of the dequeued vertex v
            for (int i=0; i < static_cast<int>(edges.size()); i++) {
                std::shared_ptr<Cell> u = edges[i].lock();

                if (u->isFree()) {
                    shortestDist = v->getDistance() + 1;

                } else {
                    std::shared_ptr<Cell> uMatch = u->getMatch().lock();
                    if (uMatch->getDistance() == INF) {
                        // Consider the pair and add it to queue
                        uMatch->setDistance(v->getDistance() + 1);
                        Q.push(std::weak_ptr<Cell>(uMatch));
                    }
                }
            }
        }
    }

    // If we could come back to NIL using alternating path of distinct
    // vertices then there is an augmenting path
    return (shortestDist != INF);
}

// Returns true if there is an augmenting path beginning with free vertex v
bool Match::dfs(std::shared_ptr<Cell> v) {
    if (v == NULL) {
        return true;
    }
    std::vector<std::weak_ptr<Cell>> edges = v->getEdgesToA();

    for (int i = 0; i < static_cast<int>(edges.size()); i++) {
        // Adjacent to v
        std::shared_ptr<Cell> u = edges[i].lock();

        double nextDist;
        if (u->isFree()) {
            nextDist = shortestDist;

        } else {
            std::shared_ptr<Cell> uMatch = u->getMatch().lock();
            nextDist = uMatch->getDistance();
        }

        // Follow the distances set by BFS
        if (nextDist == (v->getDistance() + 1)) {
            // If dfs for pair of v also returns
            // true
            if (u->isFree()) {
                Match::createMatch(v, u);
                return true;

            } else {
                std::shared_ptr<Cell> uMatch = u->getMatch().lock();
                 if (dfs(uMatch)) {
                    Match::createMatch(v, u);
                    return true;
                 }
            }
        }
    }
    // If there is no augmenting path beginning with v.
    v->setDistance(INF);
    return false;
}

// Edges are (A, B)
// P = <b = v_1>
bool Match::modDFS(std::weak_ptr<Cell> temp) {
    std::shared_ptr<Cell> v_k = temp.lock();
    // If unvisited edge going out of v_k
    std::vector<std::weak_ptr<Cell>> edges = v_k->getEdgesToA();
    bool visitedAll = false;

    for (int i = 0; i < static_cast<int>(edges.size()); i++) {
        std::shared_ptr<Cell> v = edges[i].lock();

        // Mark (v_k, v) as visited

        // If v is on P
        if (std::find(P.begin(), P.end(), v) != P.end()) {
            // Continue the DFS from v_k
            Match::modDFS(v_k);

        } else {  // v is not in P
            // Add (v_k, v) and set v_{k+1} = v
            P.push_back(std::weak_ptr<Cell>(v));

            if (v->isFree()) {
                // Augment, delete visited edges, terminate DFS
                return true;
            } else {
                // Continue DFS from v_{k+1}
                Match::modDFS(v);
            }
        }
    }

    if (visitedAll) {
        // If P = <v_1>
        for (int k = static_cast<int>(P.size()) - 1; k > 0; k--) {
            std::shared_ptr<Cell> v_k = P[k].lock();
            if (v_k == v_1) {
                // Delete visited edges and terminate DFS
                return false;
            }
            // Delete v_k from P and continue from v_{k-1}
            P.pop_back();
            Match::modDFS(P.back());
        }
    }

    return false;
}

// Forms a match between v and u and updates their capacities
void Match::createMatch(std::shared_ptr<Cell> v,
    std::shared_ptr<Cell> u) {
    u->setMatch(std::weak_ptr<Cell>(v));
    v->setMatch(std::weak_ptr<Cell>(u));

    int newCap = std::min(v->getWeightA(), u->getWeightB());
    u->setCapacity(newCap);
    v->setCapacity(newCap);
}
