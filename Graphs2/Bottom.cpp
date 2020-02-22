/*
We will use the following (standard) definitions from graph theory. Let V be a non-empty and finite set, its elements being called vertices (or nodes). Let E be a subset of the Cartesian product V×V, its elements being called edges. Then G=(V,E) is called a directed graph.

Let n be a positive integer, and let p=(e1,…,en) be a sequence of length n of edges ei∈E such that ei=(vi,vi+1)for a sequence of vertices (v1,…,vn+1). Then p is called a path from vertex v1 to vertex vn+1 in G and we say that vn+1 is reachable from v1, writing (v1→vn+1).

Here are some new definitions. A node v in a graph G=(V,E) is called a sink, if for every node w in G that is reachable from v, v is also reachable from w. The bottom of a graph is the subset of all nodes that are sinks, i.e., bottom(G)={v∈V∣∀w∈V:(v→w)⇒(w→v)}. You have to calculate the bottom of certain graphs.

Input Specification

The input contains several test cases, each of which corresponds to a directed graph G. Each test case starts with an integer number v, denoting the number of vertices of G=(V,E) where the vertices will be identified by the integer numbers in the set V={1,…,v}. You may assume that 1≤v≤5000. That is followed by a non-negative integer e and, thereafter, e pairs of vertex identifiers v1,w1,…,ve,we with the meaning that (vi,wi)∈E. There are no edges other than specified by these pairs. The last test case is followed by a zero.

Output Specification

For each test case output the bottom of the specified graph on a single line. To this end, print the numbers of all nodes that are sinks in sorted order separated by a single space character. If the bottom is empty, print an empty line.

Sample Input

3 3
1 3 2 3 3 1
2 1
1 2
0

Sample Output

1 3
2
 */

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
    
    int flag = 1;
    vector<int> ans;
    vector<int> bottom;
    for(int i = 0 ; i < k ; i++){
        for(int j = 0 ; j < SCC[i].size(); j++){
            ans.push_back(SCC[i][j]);
        }
        for(int m = 0 ; m < ans.size() ; m++){
            int node = ans[m];
            for(int j = 0 ; j < edges[node].size() ; j++){
                int new_node = edges[node][j];
                vector<int> :: iterator it;
                it = find(ans.begin(), ans.end(), new_node);
                if(it == ans.end()){
                    flag = 0;
                    break;
                }
            }
            if(flag == 0)
                break;
        }
        if(flag == 1){
            for(int j = 0 ; j < ans.size() ; j++)
                bottom.push_back(ans[j]);
        }
        flag = 1;
        ans.clear();
    }
    sort(bottom.begin(), bottom.end());
    for(int i = 0 ; i < bottom.size() ; i++)
        cout << bottom[i] + 1 << " ";
    cout << endl;
}

int main(){
    while(true){
        int n;
        cin >> n;
        if(n == 0)
            break;
        
        vector<int>* edges = new vector<int>[n];
        vector<int>* edgesT = new vector<int>[n];
        int e;
        cin >> e;
        for(int i = 0 ; i < e ; i++){
            int x, y;
            cin >> x >> y;
            edges[x-1].push_back(y-1);
            edgesT[y-1].push_back(x-1);
        }
    
        getSCC(edges, edgesT, n);
    
        delete [] edges;
        delete [] edgesT;
    }
    return 0;
}
