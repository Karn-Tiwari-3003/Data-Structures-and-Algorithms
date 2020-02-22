/* Algorithm for bipartite for connected graph */

#include<bits/stdc++.h>
using namespace std;

bool bipartite(vector<int>* edges, int n){
    unordered_set<int> sets[2];
    queue<int> pending;
    
    sets[0].insert(0);
    pending.push(0);
    
    while(!pending.empty()){
        int current = pending.front();
        pending.pop();
        int currentSet = sets[0].count(current) > 0 ? 0 : 1;
        for(int i = 0 ; i < edges[current].size() ; i++){
            int neighbour = edges[current][i];
            if(sets[0].count(neighbour) == 0 && sets[1].count(neighbour) == 0){
                sets[1-currentSet].insert(neighbour);
                pending.push(neighbour);
            }
            else if(sets[currentSet].count(neighbour) > 0)
                return false;
       }
    }
    return true;
}

int main(){
    // Number of vertices and edges
    int n, m;
    cin >> n >> m;
    vector<int>* edges = new vector<int>[n];
    for(int i = 0 ; i < m ; i++){
        int j, k;
        cin >> j >> k;
        edges[j].push_back(k);
        edges[k].push_back(j);
    }
    bool ans = bipartite(edges, n);
    if(ans)
        cout << "BICOLORABLE" << endl;
    else
        cout << "NOT BICOLORABLE" << endl;
    delete [] edges;
    return 0;
}
