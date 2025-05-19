// https://leetcode.com/problems/graph-valid-tree/

#include<iostream>
#include<vector>
using namespace std;

typedef vector<vector<int>> GRAPH;

void add_undirected_edge(GRAPH &graph, int from, int to) {
	graph[from].push_back(to);
	graph[to].push_back(from);
}

bool dfs(GRAPH &graph, int node, vector<bool> &visited, int parent = -1) {
	visited[node] = true;

	for (int neighbour : graph[node]) {
		if (neighbour == parent)
			continue;	// Avoid fake undirected edge cycle

		if (visited[neighbour])
			return true;	// cycle

		if (dfs(graph, neighbour, visited, node))
			return true;
	}
	return false;
}

bool has_cycle(GRAPH &graph) {
	int nodes = graph.size();
	vector<bool> visited(nodes);

	for (int i = 0; i < nodes; ++i) {	// handle separate CCs
		if (!visited[i] && dfs(graph, i, visited))
			return true;
	}
	return false;
}

class Solution {
public:
	bool validTree(int nodes, vector<vector<int>> &edges) {
		if ((int) edges.size()  != nodes - 1)
			return false;	// tree must be n-1 edges. Otherwise cycle

		GRAPH graph(nodes);

		for (auto &edge : edges)
			add_undirected_edge(graph, edge[0], edge[1]);

		return !has_cycle(graph);
	}
};

int main() {

	return 0;
}
