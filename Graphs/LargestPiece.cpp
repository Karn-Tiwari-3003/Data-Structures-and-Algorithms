/*
Its Gary's birthday today and he has ordered his favourite square cake consisting of '0's and '1's . But Gary wants the biggest piece of '1's and no '0's . A piece of cake is defined as a part which consist of only '1's, and all '1's share an edge with eachother on the cake. Given the size of cake N and the cake , can you find the size of the biggest piece of '1's for Gary ?
Constraints :
1<=N<=50
Input Format :

Line 1 : An integer N denoting the size of cake 
Next N lines : N characters denoting the cake

Output Format :

Size of the biggest piece of '1's and no '0's

Sample Input :

2
11
01

Sample Output :

3

 */

#include<bits/stdc++.h>
#define NMAX 55
char cake[NMAX][NMAX];
using namespace std;

int xdir[4] = {0,0,-1,1};
int ydir[4] = {-1,1,0,0};

bool eligible(int i, int j, int n){
    if(i>=0 && j>=0 && i<n && j<n)
        return true;
    return false;
}

int dfs(char cake[NMAX][NMAX], int n, int i, int j, bool visited[NMAX][NMAX]){
    visited[i][j] = true;
    int ans = 1;
    for(int k = 0 ; k < 4 ; k++){
        int dx = i + xdir[k];
        int dy = j + ydir[k];
        if(eligible(dx,dy,n) && cake[dx][dy] == '1' && visited[dx][dy] == false){
            ans += dfs(cake, n, dx, dy, visited);
        }
    }
    return ans;
}

int solve(int n,char cake[NMAX][NMAX])
{
	bool visited[NMAX][NMAX];
    memset(visited,false,sizeof(visited));
    int max_piece = INT_MIN;
    
    for(int i = 0 ; i < n ; i++){
        for(int j = 0 ; j < n ; j++){
            int curr_piece = 0;
            if(cake[i][j] == '1'){
               curr_piece = dfs(cake, n, i, j, visited);
            }
            max_piece = max(max_piece, curr_piece);
        }
    }
    return max_piece;
}

int main()
{
	int n;
	cin>>n;
	for(int i=0;i<n;i++)
	{
		scanf("%s",cake[i]);
	}
	cout<<solve(n,cake)<<endl;
}
