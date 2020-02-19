/*
Given an undirected, connected and weighted graph G(V, E) with V number of vertices (which are numbered from 0 to V-1) and E number of edges.
Find and print the Minimum Spanning Tree (MST) using Prim's algorithm.
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

int getMin(int* weight, bool* visited, int n){
    int min = INT_MAX, min_index;
    
    for(int i = 0 ; i < n ; i++){
        if(!visited[i] && weight[i] < min){
            min_index = i;
            min = weight[i];
        }
    }
    return min_index;
}

void printMst(int** edge, int* parent, int n){
    for(int i = 1 ; i < n ; i++){
        if(i < parent[i])
            cout << i << " " << parent[i] << " " << edge[i][parent[i]] << endl;
        else
            cout << parent[i] << " " << i << " " << edge[i][parent[i]] << endl;
    }
}

void prim(int** edge, int n, int E){
    int* parent = new int[n];
    int* weight = new int[n];
    bool* visited = new bool[n];
    for(int i = 0 ; i < n ; i++){
        parent[i] = -1;
        weight[i] = INT_MAX;
        visited[i] = false;
    }

    weight[0] = 0;
    
    for(int j = 0 ; j < n-1 ; j++){
        int curr_index = getMin(weight, visited, n);
        visited[curr_index] = true;
        
        for(int i = 0 ; i < n ; i++){
            if(edge[curr_index][i] && !visited[i] && edge[curr_index][i] < weight[i]){
                weight[i] = edge[curr_index][i];
                parent[i] = curr_index;
            }
        }
    }
    
    printMst(edge, parent, n);
}

int main()
{
    int n, E;
    cin >> n >> E;
    int** edges = new int*[n];
    for(int i = 0 ; i < n ; i++){
        edges[i] = new int[n];
        for(int j = 0 ; j < n ; j++)
            edges[i][j] = 0;
    }
    
    for(int i = 0 ; i < E ; i++){
        int s, d, w;
        cin >> s >> d >> w;
        edges[s][d] = w;
        edges[d][s] = w;
    }
    
    prim(edges, n, E);
    
    for(int i = 0 ; i < n ; i++){
        delete[] edges[i];
    }
    delete[] edges;
    return 0;
}
