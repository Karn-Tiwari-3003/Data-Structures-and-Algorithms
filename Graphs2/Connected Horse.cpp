/* 
You all must be familiar with the chess-board having 8*8 squares of alternate black and white cells. Well, here we have for you a similar 
N*M size board with similar arrangement of black and white cells.A few of these cells have Horses placed over them. Each horse is unique. Now these horses are not the 
usual horses which could jump to any of the 8 positions they usually jump in. They can move only if there is another horse on one of the 8-positions that it can     go to usually and then both the horses will swap their positions. This swapping can happen infinitely times.
A photographer was assigned to take a picture of all the different ways that the horses occupy the board! Given the state of the board, calculate answer. Sincethis answer may be quite large, calculate in modulo 
10^9+7

Input:
First line contains 
T which is the number of test cases.
T test cases follow first line of each containing three integers 
N, M and Q where N,M is the size of the board and Q is the number of horses on it.
Q lines follow each containing the 2 integers 
X and Y which are the coordinates of the Horses.

Output:
For each test case, output the number of photographs taken by photographer.

Constraints:
 1<=T<=10
 1<=N,M<=1000
 1<=Q<=N*M
 */
 
 #include<bits/stdc++.h>
#define MAXN 1005
#define mod 1000000007
#define ll long long int
using namespace std;

int xdir[8] = {1,1,-1,-1,2,2,-2,-2};
int ydir[8] = {2,-2,2,-2,1,-1,1,-1};

bool eligible(int n, int m, int dx, int dy){
    if(dx>=0 && dy>=0 && dx < n && dy < m)
        return true;
    return false;
}

ll dfs(bool arr[][MAXN], int n, int m, int i, int j){
    arr[i][j] = false;
    
    ll ans = 1;
    
    for(int k = 0 ; k < 8 ; k++){
        int dx = i + xdir[k];
        int dy = j + ydir[k];
        if(eligible(n,m,dx,dy) && arr[dx][dy]){
            ans += dfs(arr, n, m, dx, dy);
        }
    }
    return ans;
}

int main()
{
	int t;
    cin >> t;
    while(t--){
        int n, m, q;
        cin >> n >> m >> q;
        bool arr[MAXN][MAXN];
        memset(arr, false, sizeof(arr));
        for(int i = 0 ; i < q ; i++){
            int x, y;
            cin >> x >> y;
            arr[x-1][y-1] = true;
        }
        vector<ll> v;
        ll ans;
        for(int i = 0 ; i < n ; i++){
            for(int j = 0 ; j < m ; j++){
                if(arr[i][j]){
                    ans = dfs(arr, n, m, i, j);
                    v.push_back(ans);
                }
            }
        }
        ll count = 1;
        int max = 0;
        for(int i = 0 ; i < v.size() ; i++){
            if(v[i] > max)
                max = v[i];
        }
        ll fact[max];
        fact[0] = 1;
        for(int i = 1 ; i < max ; i++){
            fact[i] = ((fact[i-1]%mod)*((i+1)%mod))%mod;
        }
        
        int temp;
        for(int i = 0 ; i < v.size() ; i++){
            temp = fact[v[i]-1];
            count = ((count%mod)*(temp%mod))%mod;
        }
        cout << count << endl;
    }
	return 0;
}
