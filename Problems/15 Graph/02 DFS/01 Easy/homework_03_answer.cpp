#include "bits/stdc++.h"
using namespace std;
#define ll long long
#define get_shit_done freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout); 

class Solution {
	void dfs(int node, vector<vector<int>>& adj, vector<bool>& vis) {
		vis[node] = 1;

		for (auto& v : adj[node]) {
			if (vis[v]) continue;
			dfs(v, adj, vis);
		}
	}

public:
	int countComponents(int n, vector<vector<int>>& edges) {
		vector<vector<int>> adj(n);

		for (auto edge : edges) {
			int u = edge[0], v = edge[1];
			adj[u].push_back(v);
			adj[v].push_back(u);
		}

		int res = 0;
		vector<bool> vis(n, false);

		for (int i = 0; i < n; ++i) {
			if (vis[i]) continue;
			res++;
			dfs(i, adj, vis);
		}
		return res;
	}


};


int main() {
	get_shit_done


}

