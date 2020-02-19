/*
Given an undirected, connected and weighted graph G(V, E) with V number of vertices (which are numbered from 0 to V-1) and E number of edges.
Find and print the shortest distance from the source vertex (i.e. Vertex 0) to all other vertices (including source vertex also) using Dijkstra's Algorithm.
Print the ith vertex number and the distance from source in one line separated by space. Print different vertices in different lines.
Note : Order of vertices in output doesn't matter.
Input Format :

Line 1: Two Integers V and E (separated by space)
Next E lines : Three integers ei, ej and wi, denoting that there exists an edge between vertex ei and vertex ej with weight wi (separated by space)

Output Format :

In different lines, ith vertex number and its distance from source (separated by space)

Constraints :
2 <= V, E <= 10^5
Sample Input 1 :

4 4
0 1 3
0 3 5
1 2 1
2 3 8

Sample Output 1 :

0 0
1 3
2 4
3 5

 */

#include<bits/stdc++.h>
using namespace std;

int getMin(int* dis, bool* visited, int n){
    int min = INT_MAX, min_index;
    
    for(int i = 0 ; i < n ; i++){
        if(!visited[i] && dis[i] < min){
            min_index = i;
            min = dis[i];
        }
    }
    return min_index;
}

void printDis(int* dis, int n){
    for(int i = 0 ; i < n ; i++)
        cout << i << " " << dis[i] << endl;
}

void dijkstra(int** edge, int n, int E){
    int* dis = new int[n];
    bool* visited = new bool[n];
    for(int i = 0 ; i < n ; i++){
        dis[i] = INT_MAX;
        visited[i] = false;
    }

    dis[0] = 0;
    
    for(int j = 0 ; j < n-1 ; j++){
        int curr_index = getMin(dis, visited, n);
        visited[curr_index] = true;
        
        for(int i = 0 ; i < n ; i++){
            if(edge[curr_index][i] && !visited[i] && edge[curr_index][i] + dis[curr_index] < dis[i]){
                dis[i] = edge[curr_index][i] + dis[curr_index];
            }
        }
    }
    
    printDis(dis, n);
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
    
    dijkstra(edges, n, E);
    
    for(int i = 0 ; i < n ; i++){
        delete[] edges[i];
    }
    delete[] edges;
    return 0;
}
