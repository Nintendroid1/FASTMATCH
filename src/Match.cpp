#include "../include/Match.hpp"

// Returns true if there is an augmenting path, else returns 
// false 
bool Match::bfs() { 
    // queue<Vertex> Q; //an Vertex queue 
  
    // // First layer of vertices (set distance as 0) 
    // for (int u=1; u<=nA; u++) 
    // { 
    //     // If this is a free vertex, add it to queue 
    //     if (pairU[u]==NIL) 
    //     { 
    //         // u is not matched 
    //         dist[u] = 0; 
    //         Q.push(u); 
    //     } 
  
    //     // Else set distance as infinite so that this vertex 
    //     // is considered next time 
    //     else dist[u] = INF; 
    // } 
  
    // // Initialize distance to NIL as infinite 
    // dist[NIL] = INF; 
  
    // // Q is going to contain vertices of left side only.  
    // while (!Q.empty()) 
    // { 
    //     // Dequeue a vertex 
    //     int u = Q.front(); 
    //     Q.pop(); 
  
    //     // If this node is not NIL and can provide a shorter path to NIL 
    //     if (dist[u] < dist[NIL]) 
    //     { 
    //         // Get all adjacent vertices of the dequeued vertex u 
    //         list<int>::iterator i; 
    //         for (i=adj[u].begin(); i!=adj[u].end(); ++i) 
    //         { 
    //             int v = *i; 
  
    //             // If pair of v is not considered so far 
    //             // (v, pairV[V]) is not yet explored edge. 
    //             if (dist[pairV[v]] == INF) 
    //             { 
    //                 // Consider the pair and add it to queue 
    //                 dist[pairV[v]] = dist[u] + 1; 
    //                 Q.push(pairV[v]); 
    //             } 
    //         } 
    //     } 
    // } 
  
    // // If we could come back to NIL using alternating path of distinct 
    // // vertices then there is an augmenting path 
    // return (dist[NIL] != INF); 
    return true;
} 

// Returns true if there is an augmenting path beginning with free vertex u 
bool Match::dfs(Vertex v) { 
    // if (u != NULL) 
    // { 
    //     vector<Vertex>::iterator i; 
    //     vector<Vertex> edgesU = u.getEdges();
    //     for (i=edgesU.begin(); i!=edgesU.end(); ++i) 
    //     { 
    //         // Adjacent to u 
    //         Vertex v = *i; 
  
    //         // Follow the distances set by BFS 
    //         if (dist[pairB[v]] == dist[u]+1) 
    //         { 
    //             // If dfs for pair of v also returns 
    //             // true 
    //             if (dfs(pairB[v]) == true) 
    //             { 
    //                 pairB[v] = u; 
    //                 pairA[u] = v; 
    //                 return true; 
    //             } 
    //         } 
    //     } 
  
    //     // If there is no augmenting path beginning with u. 
    //     dist[u] = INF; 
    //     return false; 
    // } 
    return true; 
}