/*
An island is a small piece of land surrounded by water . A group of islands is said to be connected if we can reach from any given island to any other island in the same group . Given N islands (numbered from 1 to N) and two lists of size M (u and v) denoting island u[i] is connected to island v[i] and vice versa . Can you count the number of connected groups of islands.
Constraints :
1<=N<=100
1<=M<=(N*(N-1))/2
1<=u[i],v[i]<=N
Input Format :

Line 1 : Two integers N and M
Line 2 : List u of size of M
Line 3 : List v of size of M

Output Return Format :

The count the number of connected groups of islands

Sample Input :

2 1
1
2

Sample Output :

1 

 */

#include<bits/stdc++.h>
using namespace std;

int print(int** edges , int n , int sv , bool* visited){
    list<int> q;
    int count = 0;
    for(int i = 0 ; i < n ; i++){
        if(visited[i]==false){
            q.push_back(i);
            visited[i] = true;
            while(!q.empty()){
                sv = q.front();
                q.pop_front();
                for(int i = 0 ; i < n ; i++){
                    if(edges[sv][i] == 1 && !visited[i]){
                        q.push_back(i);
                        visited[i] = true;
                    }
                }
            }
            count++;
        }
    }
    return count;
}

int solve(int n,int m,vector<int>u,vector<int>v)
{
	// Write your code here .
    int** edges = new int*[n]; // dynamic 2D allocation
    for(int i = 0 ; i < n ; i++){
        edges[i] = new int[n];
        for(int j = 0 ; j < n ; j++)
            edges[i][j] = 0;
    }
    for(int i = 0 ; i < m ; i++){
        edges[u[i]-1][v[i]-1] = 1;
        edges[v[i]-1][u[i]-1] = 1;
    }
    bool visited[n];
    for(int i = 0 ; i < n ;i++)
        visited[i] = false;
    
    return print(edges, n, 0, visited);
}

int main()
{
	int n,m;
	vector<int>u,v;
	cin>>n>>m;
	for(int i=0;i<m;i++)
	{
		int x;
		cin>>x;
		u.push_back(x);
	}
	for(int i=0;i<m;i++)
	{
		int x;
		cin>>x;
		v.push_back(x);
	}
	cout<<solve(n,m,u,v)<<endl;
}
