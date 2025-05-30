// https://leetcode.com/problems/reorder-routes-to-make-all-paths-lead-to-the-city-zero/

#include<iostream>
#include<vector>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <map>
using namespace std;

/*
 * In a tree structure, we know there is ONLY ONE path from a node to another
 * Hence, the path from any node to node(0) is only 1 and well know in the undirected graph
 *
 * So all what we need is to DFS from each node and get all such paths
 *
 * Reverse thinking here makes our life easier
 * Instead of DFS from each node to node(0)
 * A single DFS from node(0) to all others is the same, just the opposite direction
 *
 * So, run this DFS(0), it will tell you the exact direction where this edge should be.
 * 		If the edge is not in the direction we want, we flip it
 *
 * 		But as we do the reverse of the problem, if the edge exists, then we flip it
 *
 * Overall
 * 	Build undirected graph, but keep a flag to know if this is the old edge or not
 * 	Then DFS from node(0)
 *
 * Example: assume input graph is simple chain: (0, 1), (1, 2), (3, 2), (4, 3)
 *
 * DFS from 0 results in directed tree: [0->1->2->3->4]
 * 		Reverse it, so the tree that must exist is [4->3->2->1->0]
 * 		Which means we need to flip 2 edges (0, 1) and (1, 2)
 *
 * 		In the DFS below: (0, 1) will exist, so we count it (due to reversing)
 *
 */


struct edge {
	int to;
	bool built;
};

typedef vector<vector<edge>> GRAPH;

void add_undirected_edge(GRAPH &graph, int from, int to) {
	// Add the given edge and marked as built already.
	graph[from].push_back( { to, true });
	graph[to].push_back( { from, false });	// NOT built
}

void dfs(GRAPH &graph, int node, vector<bool> &visited, int &reorient_cnt) {
	visited[node] = true;

	for (edge &e : graph[node]) {
		if (!visited[e.to]) {
			reorient_cnt += e.built;	//
			dfs(graph, e.to, visited, reorient_cnt);
		}
	}
}

class Solution {
public:
	int minReorder(int nodes, vector<vector<int>> &connections) {
		int reorient_cnt = 0;
		GRAPH graph(nodes);
		vector<bool> visited(nodes);

		for (auto &edge : connections)
			add_undirected_edge(graph, edge[0], edge[1]);

		dfs(graph, 0, visited, reorient_cnt);
		return reorient_cnt;
	}
};

int main() {

	return 0;
}
