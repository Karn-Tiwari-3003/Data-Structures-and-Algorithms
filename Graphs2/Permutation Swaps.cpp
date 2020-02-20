/* Kevin has a permutation P of N integers 1, 2, ..., N, but he doesn't like it. Kevin wants to get a permutation Q.

Also he believes that there are M good pairs of integers (ai , bi). Kevin can perform following operation with his permutation:

Swap Px and Py only if (x, y) is a good pair.
Help him and tell if Kevin can obtain permutation Q using such operations. 

Input format:

The first line of input will contain an integer T, denoting the number of test cases.
Each test case starts with two space-separated integers N and M. The next line contains N space-separated integers Pi. The next line contains N space-separated integers Qi. Each of the next M lines contains two space-separated integers ai and bi.

Output format:

For every test case output "YES" (without quotes) if Kevin can obtain permutation Q and "NO" otherwise.

Constraints:

1 ≤ T ≤ 10
2 ≤ N ≤ 100000
1 ≤ M ≤ 100000
1 ≤ Pi, Qi ≤ N. Pi and Qi are all distinct.
1 ≤ ai < bi ≤ N

*/

#include<bits/stdc++.h>
using namespace std;

void dfs(vector<int>* edges, int start, unordered_set<int>* component, bool* visited){
    visited[start] = true;
    component->insert(start);
    
    for(int i = 0 ; i < edges[start].size() ; i++){
        int next = edges[start][i];
        if(!visited[next]){
            dfs(edges, next, component, visited);
        }
    }
}

unordered_set<unordered_set<int>*>* getComponents(vector<int>* edges, int n){
    bool* visited = new bool[n];
    memset(visited, false, sizeof(visited));
    
    unordered_set<unordered_set<int>*>* output = new unordered_set<unordered_set<int>*>();
    
    for(int i = 0 ; i < n ; i++){
        if(!visited[i]){
            unordered_set<int>* component = new unordered_set<int>();
            dfs(edges, i, component, visited);
            output->insert(component);
        }
    }
    delete [] visited;
    return output;
}

int main()
{
	int t;
    cin >> t;
    while(t--){
        int n, m;
        cin >> n >> m;
        vector<int> p, q;
        for(int i = 0 ; i < n ; i++){
            int x;
            cin >> x;
            p.push_back(x);
        }
        
        for(int i = 0 ; i < n ; i++){
            int x;
            cin >> x;
            q.push_back(x);
        }
        
        vector<int>* edges = new vector<int>[n];
        for(int i = 0 ; i < m ; i++){
            int j, k;
	        cin >> j >> k;
	        edges[j-1].push_back(k-1);
	        edges[k-1].push_back(j-1);
        }

        unordered_set<unordered_set<int>*>* components = getComponents(edges, n);
	      unordered_set<unordered_set<int>*> :: iterator it1 = components->begin();
        int flag = 1;
        int i = 0;
	      while(it1 != components->end() && flag == 1){
	        unordered_set<int>* component = *it1;
	        unordered_set<int> :: iterator it2 = component->begin();
            int ans = 0;
	        while(it2 != component->end() && flag == 1){
                ans ^= p[*it2]^q[*it2]; 
	            it2++;
	        }
            if(ans != 0)
                flag = 0;
            
	        it1++;
	        delete component;
	      }
	      delete components;
	      delete [] edges;
        
        if(flag == 1)
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }
	return 0;
}
