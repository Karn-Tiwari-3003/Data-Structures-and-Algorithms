#include<bits/stdc++.h>
using namespace std;

void dfs(vector<int>* edges, stack<int>& finishedVertices, bool* visited, int n, int start){
    visited[start] = true;
    for(int i = 0 ; i < edges[start].size() ; i++){
        int node = edges[start][i];
        if(!visited[node]){
            dfs(edges, finishedVertices, visited, n, node);
        }
    }
    finishedVertices.push(start);
}

void dfs_reverse(vector<int>* edgesT, bool* visited, unordered_map<int,vector<int>>& SCC, int node, int k){
    SCC[k].push_back(node);
    visited[node] = true;
    
    for(int i = 0 ; i < edgesT[node].size() ; i++){
        int new_node = edgesT[node][i];
        if(!visited[new_node]){
            dfs_reverse(edgesT, visited, SCC, new_node, k);
        }
    }
}

void getSCC(vector<int>* edges, vector<int>* edgesT, int n){
    bool* visited = new bool[n];
    memset(visited, false, sizeof(visited));
    
    stack<int> finishedVertices;
    for(int i = 0 ; i < n ; i++){
        if(!visited[i]){
            dfs(edges, finishedVertices, visited, n, i);
        }
    }
    
    unordered_map<int,vector<int>> SCC;
    int k = 0;
    
    for(int i = 0 ; i < n ; i++){
        visited[i] = false;
    }
    
    while(!finishedVertices.empty()){
        int node = finishedVertices.top();
        finishedVertices.pop();
        
        if(!visited[node]){
            dfs_reverse(edgesT, visited, SCC, node, k);
            k++;
        }
    }
    
    for(int i = 0 ; i < k ; i++)
    {
        cout << "Connect component " << i << ": ";
        for(int j=0 ; j<SCC[i].size() ; j++)
            cout << SCC[i][j] + 1 << " ";
        cout << endl;
    }
}

int main(){
    int n;
    cin >> n;
    vector<int>* edges = new vector<int>[n];
    vector<int>* edgesT = new vector<int>[n];
    int m;
    cin >> m;
    for(int i = 0 ; i < m ; i++){
        int x, y;
        cin >> x >> y;
        edges[x-1].push_back(y-1);
        edgesT[y-1].push_back(x-1);
    }
    
    getSCC(edges, edgesT, n);
    
    delete [] edges;
    delete [] edgesT;
    return 0;
}
