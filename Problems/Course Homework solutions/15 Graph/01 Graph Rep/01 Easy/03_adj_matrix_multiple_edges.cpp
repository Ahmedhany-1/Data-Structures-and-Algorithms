#include "bits/stdc++.h"
using namespace std;
#define ll long long
#define get_shit_done freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout); 
typedef vector<vector<vector<int>>> GRAPH;

void add_directed_edge(GRAPH& graph, int from, int to, int cost) {
	graph[from][to].emplace_back(cost);
}


void print_adjaceny_matrix(GRAPH& graph) {
	int nodes = graph.size();
	for (int from = 0; from < nodes; ++from) {
		for (int to = 0; to < nodes; ++to) {
			for (int weight : graph[from][to])
				cout << "From " << from << " to " << to
				<< " the cost is " << weight << "\n";
		}
	}
}

int main() {
	get_shit_done
		int n, m; cin >> n >> m;
	GRAPH g(n, vector<vector<int>>(n));

	for (int i = 0, u, v, c; i < m; i++) {
		cin >> u >> v >> c;
		add_directed_edge(g, u, v, c);
	}
	print_adjaceny_matrix(g);

}

/*
Output
From 0 to 1 the cost is 10
From 0 to 1 the cost is 7
From 0 to 4 the cost is 52
From 0 to 4 the cost is 30
From 1 to 2 the cost is 7
From 2 to 3 the cost is 9
From 2 to 3 the cost is 15
From 2 to 4 the cost is 36
From 3 to 4 the cost is 50
From 4 to 0 the cost is 150


O(V^2 + E) for space complexity
O(1) to check edge (u, v)

*/