#include "../include/Match.hpp"

Match::Match(vector<Cell> cs) {
    cells = cs;
}

//Hopcroft-Karp
void Match::modHK() {
    int iteration = 0;
    
    cout << "Starting BFS" << endl;
    while(bfs()) {
        cout << "BFS Iteration " << iteration << endl;
        for(int i = 0; i < (int) cells.size(); i++) {
            Cell c = cells[i];

            Vertex vCenterA = c.getVertexA();

            //Split by class
            if(vCenterA.isFree()) { 
                cout << "DFS" << endl;
                //dfs(&c);
            }
        }
    }
}
// Returns true if there is an augmenting path, else returns 
// false 
bool Match::bfs() { 
    queue<Cell> Q;
  
    // First layer of vertices (set distance as 0) 
    for (int i=0; i < (int)cells.size(); i++) { 
        Cell& v = cells[i];

        Vertex vCenterA = v.getVertexA();

        // If this is a free vertex, add it to queue 
        if (vCenterA.isFree()) { 
            // v is not matched 
            Q.push(v);
            vCenterA.setDistance(0);  
        } 
        else {
            // Else set distance as infinite so that this vertex 
            // is considered next time 
            vCenterA.setDistance(INF); 
        }
    } 
  
    // Initialize distance to NIL as infinite 
    shortestDist = INF; 
  
    // Q is going to contain vertices of left side only. 
    while (!Q.empty()) { 
        cout << "BFS Queue" << endl;
        // Dequeue a vertex 
        Cell& v = Q.front(); 
        Q.pop(); 

        Vertex vCenterA = v.getVertexA();
  
        // If this node is not NIL and can provide a shorter path to NIL 
        if (vCenterA.getDistance() < shortestDist) {
            vector<Cell*> edges = v.getEdgesB();

            // Get all adjacent vertices of the dequeued vertex v 
            for (int i=0; i < (int)edges.size(); i++) { 
                Cell* u = edges[i]; 

                Vertex* uCenterB = u->getPointerVertexB();

                if (uCenterB->isFree()) {
                    shortestDist = vCenterA.getDistance() + 1;
                }
                else if (uCenterB->getMatch().getDistance() == INF) {
                    // Consider the pair and add it to queue
                    uCenterB->getMatch().setDistance(vCenterA.getDistance() + 1);
                    Q.push(u->getCellMatch());
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
bool Match::dfs(Cell* v) { 
    // if (v == NULL) {  
    //     return true;
    // }
    // Vertex vCenterA = v.getVertexA();
    // vector<Cell*> edges = v.getEdgesB();
    
    // for (int i = 0; i < (int) edges.size(); i++) { 
    //     // Adjacent to v 
    //     Cell* u = edges[i]; 
    //     Vertex* uCenterB = u->getPointerVertexB();

    //     double nextDist;
    //     if(uCenterB.isFree()) {
    //         nextDist = shortestDist;
    //     }
    //     else {
    //         nextDist = uCenterB->getMatch().getDistance();
    //     }

    //     // Follow the distances set by BFS 
    //     if (nextDist == (vCenterA.getDistance() + 1)) { 
    //         // If dfs for pair of v also returns 
    //         // true 
    //         if (uCenterB->isFree()) { 
    //             uCenterB->setMatch(vCenterA);
    //             vCenterA.setMatch(*u);

    //             return true; 
    //         }
    //         else {
    //             Vertex tempMatch = uCenterB->getMatch();
    //              if(dfs(&tempMatch)) {
    //                 u.setMatch(*v);
    //                 v->setMatch(u);

    //                 return true;
    //              }
    //         } 
    //     }  
    // }
    // // If there is no augmenting path beginning with v. 
    // v->setDistance(INF); 
    return false;  
}