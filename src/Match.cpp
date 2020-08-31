// Copyright 2020, Nathaniel Salazar, All rights reserved

#include "../include/Match.hpp"

Match::Match(std::vector<std::shared_ptr<Cell>> cs) {
    cells = cs;
}
// TODO(Nintendroid1) Separate algorithms to separate files
// Modified Hopcroft-Karp
void Match::modHK() {
    // Find augmenting paths and assign distances
    while (bfs()) {
        for (int i = 0; i < static_cast<int>(cells.size()); i++) {
            std::shared_ptr<Cell> c = cells[i];

            // Augment the paths
            if (c->isFree() && (c->getStatus() == ASET ||
                c->getStatus() == ALL)) {
                dfs(c);
            }
        }
    }
}

// Modified Hopcroft-Karp
void Match::modifiedHK() {
    while (bfs()) {
        for (int i = 0; i < static_cast<int>(cells.size()); i++) {
            std::shared_ptr<Cell> c = cells[i];

            // Split by class
            if (c->isFree() && c->getWeightA() > 0) {  // TODO(Nintendroid1): Avoid Repetition?
                P.clear();
                v_1 = c;
                P.push_back(std::weak_ptr<Cell>(v_1));
                modDFS(v_1);
            }
        }
    }
}

//Ford-Fulkerson
void Match::FordFulk() {
    for (int i = 0; i < static_cast<int>(cells.size()); i++) {
        std::shared_ptr<Cell> c = cells[i];

        resetVisited();

        // Augment the paths
        if (c->isFree() && (c->getStatus() == ASET ||
            c->getStatus() == ALL)) {
            ffDFS(c);
        }
    }
    resetVisited();
}

// Returns true if there is an augmenting path, else returns
// false
bool Match::bfs() {
    std::queue<std::weak_ptr<Cell>> Q;

    // First layer of vertices (set distance as 0)
    for (int i=0; i < static_cast<int>(cells.size()); i++) {
        std::shared_ptr<Cell> v = cells[i];

        if (v->getStatus() == BSET || v->getStatus() == NONE) {
            continue;
        }

        // If this is a free vertex
        // with label A, add it to queue
        if (v->isFree()) {
            // v is not matched
            v->setDistance(0);
            Q.push(std::weak_ptr<Cell>(v));
        } else {
            // Else set distance as infinite so that this vertex
            // is considered next time
            v->setDistance(INF);
        }
    }
    // Initialize distance to NIL as infinite
    shortestDist = INF;

    // Q is going to contain vertices of label A.
    while (!Q.empty()) {
        // Dequeue a vertex A
        std::shared_ptr<Cell> v = Q.front().lock();
        Q.pop();

        // If this node is not NIL and can provide a shorter path to NIL
        if (v->getDistance() < shortestDist) {
            std::vector<std::tuple<std::weak_ptr<Cell>, bool>>
                edges = v->getEdgesToA();

            // Get all adjacent vertices of the dequeued vertex v
            for (int i=0; i < static_cast<int>(edges.size()); i++) {
                std::shared_ptr<Cell> u = std::get<0>(edges[i]).lock();

                // Assign layer + 1
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
    std::vector<std::tuple<std::weak_ptr<Cell>, bool>> edges = v->getEdgesToA();

    for (int i = 0; i < static_cast<int>(edges.size()); i++) {
        // Adjacent to v
        std::shared_ptr<Cell> u = std::get<0>(edges[i]).lock();

        // Track last vertex in search path
        double nextDist;
        if (u->isFree()) {
            nextDist = shortestDist;

        } else {
            std::shared_ptr<Cell> uMatch = u->getMatch().lock();
            nextDist = uMatch->getDistance();
        }

        // Follow the distances set by BFS
        // Only consider the admissible edges
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
    // Ensure vertex is not explored twice
    v->setDistance(INF);
    return false;
}

bool Match::modBFS() {
    // // Initialize distance to NIL as infinite
    // shortestDist = INF;

    // // First layer of vertices (set distance as 0)
    // for (int i=0; i < static_cast<int>(cells.size()); i++) {
    //     std::shared_ptr<Cell> v = cells[i];

    //     // If this is a free vertex
    //     // with label A, add it to queue
    //     if (v->isFree() && v->getStatus() == ASET) {
    //         // v is not matched
    //         zeros.push_back(std::weak_ptr<Cell>(v));
    //         v->setDistance(0);

    //     } else {
    //         // Else set distance as infinite so that this vertex
    //         // is considered next time
    //         v->setDistance(INF);
    //     }
    // }

    // while(!(zeros.empty() && ones.empty() && twos.empty())) { // TODO(Nintendroid1): Why?
    //     while(zeros.empty()) {
    //         temp = zeros;
    //         zeros = ones;
    //         ones = twos;
    //         twos = temp;
    //     }

    //     std::shared_ptr<Cell> v = zeros.front().lock();
    //     zeros.pop();

    //     if (v->getDistance() > shortestDist) {
    //         continue;
    //     }

    //     // Get all adjacent vertices of the dequeued vertex v
    //     for (int i=0; i < static_cast<int>(edges.size()); i++) {
    //         std::shared_ptr<Cell> u = std::get<0>(edges[i]).lock();

    //         if (!v->isFree() && u == v->getMatch().lock()) {
    //             continue;
    //         }

    //         int dist = std::min(u->getDistance(), v->getDistance());

    //         if (!u->isFree()) {
    //             std::shared_ptr<Cell> uMatch = u->getMatch().lock();
    //             dist += std::min(u->getDistance(), uMatch->getDistance());
    //         }
            
    //         int testDist = v->getDistance() + dist;
    //         if ( testDist > shortestDist) {
    //             continue;
    //         }

    //         if (u->isFree() ||  u->getMatch().lock()->getDistance() > testDist) {
    //             if (!u->isFree()) {
    //                 std::shared_ptr<Cell> uMatch = u->getMatch().lock();
    //                 uMatch->setDistance(testDist);
    //             }

    //             if (dist == 0) {
    //                 // zeros.push_back()
    //             } else if {
    //                 // ones.push_back()
    //             } else {
    //                 // two.push_back()
    //             }
    //         }

    //     }
    // }

    // // If we could come back to NIL using alternating path of distinct
    // // vertices then there is an augmenting path
    // return (shortestDist != INF);
    return true;
}

// Edges are (A, B)
// P = <b = v_1>
bool Match::modDFS(std::weak_ptr<Cell> temp) {
    std::shared_ptr<Cell> v_k = temp.lock();

    // If unvisited edge going out of v_k
    std::vector<std::tuple<std::weak_ptr<Cell>, bool>>
        edges = v_k->getEdgesToA();

    for (int i = 0; i < static_cast<int>(edges.size()); i++) {
        std::shared_ptr<Cell> v = std::get<0>(edges[i]).lock();

        // This edge is visited
        if (std::get<1>(edges[i]) == true) {
            continue;

        } else {  // Edge is not visited
            // Mark (v_k, v) as visited
            std::get<1>(edges[i]) = true;
            visited.push_back(edges[i]);  // Edges in G
        }

        // If v is in P
        if (std::find(P.begin(), P.end(), v) != P.end()) {
            // Continue the DFS from v_k which is current iteration
            continue;

        } else {  // v is not in P
            // Add (v_k, v) and set v_{k+1} = v
            P.push_back(std::weak_ptr<Cell>(v));

            if (v->isFree()) {
                // Augment, delete visited edges, terminate DFS
                createMatch(v_k, v);
                deleteEdges();
                return true;

            } else {
                // Continue DFS from v_{k+1}
                Match::modDFS(v);
            }
        }
    }

    // No more unvisited edges out of v_k
    if (v_k == v_1) {
        // Delete visited edges and terminate DFS
        deleteEdges();

    } else {
        // Delete v_k from P and continue from v_{k-1}
        P.pop_back();
        Match::modDFS(P.back());
    }

    return false;
}

bool Match::ffDFS(std::shared_ptr<Cell> v) {
    // If unvisited edge going out of v_k
    std::vector<std::tuple<std::weak_ptr<Cell>, bool>>
        edges = v->getEdgesToA();

    for (int i = 0; i < static_cast<int>(edges.size()); i++) {
        std::shared_ptr<Cell> u = std::get<0>(edges[i]).lock();

        // This edge is visited
        if (std::get<1>(edges[i]) == true) {
            continue;

        } else {  // Edge is not visited
            // Mark (v_k, v) as visited
            std::get<1>(edges[i]) = true;
            visited.push_back(edges[i]);  // Edges in G
        }

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

void Match::augmentFlow(std::shared_ptr<Cell> v,
    std::shared_ptr<Cell> u, int bottleneck) {
        int capacity = std::min(v->getWeightA(), u->getWeightB());

        // Augment edge from A to B
        v->setForward(v->getForward() + bottleneck);
        v->setBackward(capacity - v->getForward());
}

void Match::deleteEdges() {
    for (int i = 0; i < static_cast<int>(visited.size()); i++) {
        std::shared_ptr<Cell> e = std::get<0>(visited[i]).lock();

        if (std::find(P.begin(), P.end(), e) == P.end()) {
            visited.erase(visited.begin() + 1);
        }
    }
}

// Reset the visited vertices
void Match::resetVisited() {
    for(int i = 0; i < static_cast<int>(visited.size()); i++) {
        std::get<1>(visited[i]) = false;
        visited.erase(visited.begin() + i);
    }
    visited.clear();
}
