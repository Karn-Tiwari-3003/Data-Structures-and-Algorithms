/*
Given a graph with N vertices and Two Lists (U,V) of size M where (U[i],V[i]) and (V[i],U[i]) are connected by an edge , then count the distinct 3-cycles in the graph. A 3-cycle PQR is a cycle in which (P,Q), (Q,R) and (R,P) are connected an edge.
Input Format :

Line 1 : Two integers N and M
Line 2 : List u of size of M
Line 3 : List v of size of M

Return Format :

The count the number of 3-cycles in the given Graph

Constraints :
1<=N<=100
1<=M<=(N*(N-1))/2
1<=u[i],v[i]<=N
Sample Input:

3 3
1 2 3
2 3 1

Sample Output:

1

 */


#include <bits/stdc++.h>
using namespace std;
#define MAXN 100

int solve(int n,int m,vector<int>u,vector<int>v)
{
    int edges[n][MAXN];
    memset(edges,0,sizeof(edges));
    for(int i = 0 ; i < m ; i++){
        edges[u[i]-1][v[i]-1] = 1;
        edges[v[i]-1][u[i]-1] = 1;
    }
    
    bool visited[n];
    memset(visited,false,sizeof(visited));
    int count = 0;
    
    for(int i = 0 ; i < n ; i++){
        visited[i] = true;
        vector<int> v;
        for(int j = 0 ; j < n ; j++){
            if(edges[i][j] == 1 && !visited[j]){
                v.push_back(j);
            }
        }
        for(int j = 0 ; j < v.size() ; j++){
            for(int k = 0 ; k < n ; k++){
                if(!visited[k] && edges[v[j]][k] == 1 && edges[i][k] == 1)
                    count++;
            }
        }
    }
    return count/2;
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
