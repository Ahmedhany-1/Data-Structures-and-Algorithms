// https://leetcode.com/problems/tree-diameter/
// https://www.spoj.com/problems/PT07Z/

#include<iostream>
#include<vector>
#include<queue>
using namespace std;


typedef vector<vector<int>> GRAPH;

void add_undirected_edge(GRAPH &graph, int from, int to) {
	graph[from].push_back(to);
	graph[to].push_back(from);
}

int treeDiam(GRAPH &adjList) {
	// ToDo
}

int main() {
	// This 2 lines can speed the reading with cin
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int nodes;
	cin >> nodes;

	GRAPH graph(nodes + 1);

	for (int i = 0; i < nodes - 1; i++) {
		int x, y;
		cin >> x >> y;
		add_undirected_edge(graph, x - 1, y - 1);
	}
	cout << treeDiam(graph) << "\n";

	return 0;
}
