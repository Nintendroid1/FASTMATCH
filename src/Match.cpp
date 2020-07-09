#include "../include/Match.hpp"

Match::Match(vector<Vertex> vs) {
    vertices = vs;
}

// Returns true if there is an augmenting path, else returns 
// false 
bool Match::bfs() { 
    queue<Vertex> Q;
  
    // First layer of vertices (set distance as 0) 
    for (int i=0; i < (int)vertices.size(); i++) { 
        Vertex& v = vertices[i];

        //Split by class
        if(v.getLabel() == B) {
            continue;
        }
        // If this is a free vertex, add it to queue 
        if (v.isFree()) { 
            // u is not matched 
            v.setDistance(0); 
            Q.push(v); 
        } 
        else {
            // Else set distance as infinite so that this vertex 
            // is considered next time 
            v.setDistance(INF); 
        }
    } 
  
    // Initialize distance to NIL as infinite 
    shortestDist = INF; 
  
    // Q is going to contain vertices of left side only.  
    while (!Q.empty()) { 
        // Dequeue a vertex 
        Vertex& v = Q.front(); 
        Q.pop(); 
  
        // If this node is not NIL and can provide a shorter path to NIL 
        if (v.getDistance() < shortestDist) { 
            vector<Vertex> edges = v.getEdges();
            
            // Get all adjacent vertices of the dequeued vertex v 
            for (int i=0; i < (int)edges.size(); i++) { 
                Vertex u = edges[i]; 
                // cout << (edges[0]).getX() << endl; //TODO WHY is first vertex's x value invalid?

                if (u.isFree()) { 
                    shortestDist = v.getDistance() + 1;
                }
                else if (u.getDistance() == INF) {
                    // Consider the pair and add it to queue 
                    u.setDistance(v.getDistance() + 1); 
                    Q.push(*u.getMatch());
                } 
                // cout << "V: " << v.getLabel() << " (" << v.getX() << ", " << v.getY() << ")" << endl;
                // cout << "U: " << u.getLabel() << " (" << u.getX() << ", " << u.getY() << ")" << endl << endl; 
            } 
        } 
    } 
  
    // If we could come back to NIL using alternating path of distinct 
    // vertices then there is an augmenting path 
    return (shortestDist != INF); 
} 

// Returns true if there is an augmenting path beginning with free vertex v 
bool Match::dfs(Vertex v) { 
    if (&v == NULL) {  
        return true;
    }
    vector<Vertex> edges = v.getEdges(); //TODO Iterator?
    
    for (int i = 0; i < (int) edges.size(); i++) { 
        // Adjacent to v 
        Vertex u = edges[i]; 
        
        double nextDist;
        if(u.isFree()) {
            nextDist = shortestDist;
        }
        else {
            nextDist = u.getMatch()->getDistance();
        }

        // Follow the distances set by BFS 
        if (nextDist == v.getDistance() + 1) { 
            // If dfs for pair of v also returns 
            // true 
            if (u.isFree() || dfs(*u.getMatch())) { 
                u.setMatch(&v);
                return true; 
            } 
        }  
    }
    // If there is no augmenting path beginning with v. 
    v.setDistance(INF); 
    return false;  
}