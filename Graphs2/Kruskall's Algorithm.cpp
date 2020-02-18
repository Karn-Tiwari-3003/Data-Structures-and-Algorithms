/*
Given an undirected, connected and weighted graph G(V, E) with V number of vertices (which are numbered from 0 to V-1) and E number of edges.
Find and print the Minimum Spanning Tree (MST) using Kruskal's algorithm.
For printing MST follow the steps -
1. In one line, print an edge which is part of MST in the format -

v1 v2 w

where, v1 and v2 are the vertices of the edge which is included in MST and whose weight is w. And v1 <= v2 i.e. print the smaller vertex first while printing an edge.
2. Print V-1 edges in above format in different lines.
Note : Order of different edges doesn't matter.
Input Format :

Line 1: Two Integers V and E (separated by space)
Next E lines : Three integers ei, ej and wi, denoting that there exists an edge between vertex ei and vertex ej with weight wi (separated by space)

Output Format :

MST

Constraints :
2 <= V, E <= 10^5
Sample Input 1 :

4 4
0 1 3
0 3 5
1 2 1
2 3 8
 */

#include<bits/stdc++.h>
using namespace std;

class Edge{
    public:
    int src, des, weight;
};

bool compare(Edge e1, Edge e2){
    return e1.weight < e2.weight;
}

int getParent(int node, int* parent){
    if(node != parent[node])
        return getParent(parent[node], parent);
    return node;
}

Edge* kruskal(Edge* edge, int n, int E){
    Edge* output = new Edge[n-1];
    int count = 0;
    int i = 0;
    
    int* parent = new int[n];
    for(int i = 0 ; i < n ; i++){
        parent[i] = i;
    }
    
    while(count < (n-1)){
        int srcParent = getParent(edge[i].src, parent);
        int desParent = getParent(edge[i].des, parent);
        if(srcParent != desParent){
            output[count] = edge[i];
            count += 1;
            parent[srcParent] = desParent; 
        }
        i += 1;
    }
    return output;
}

int main()
{
    int n, E;
    cin >> n >> E;
    Edge* edge = new Edge[E];
    
    for(int i = 0 ; i < E ; i++){
        int s, d, w;
        cin >> s >> d >> w;
        edge[i].src = s;
        edge[i].des = d;
        edge[i].weight = w;
    }
    
    sort(edge, edge + E, compare);
    Edge* output = kruskal(edge, n, E);
    
    for(int i = 0 ; i < n-1 ; i++){
        if(output[i].src < output[i].des)
            cout << output[i].src << " " << output[i].des << " " << output[i].weight << endl;
        else
            cout << output[i].des << " " << output[i].src << " " << output[i].weight << endl;
    }
    return 0;
}
