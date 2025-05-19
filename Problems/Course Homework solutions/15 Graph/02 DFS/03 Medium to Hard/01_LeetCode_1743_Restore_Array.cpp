// https://leetcode.com/problems/restore-the-array-from-adjacent-pairs/

#include<iostream>
#include<vector>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
using namespace std;

/*
 * Assume we have original array: 1, 2, 3, 4, 5
 * 	The adjacent might be given as:
 * 		(1, 2), (2, 3), (4, 3), (4, 5)
 *
 * 	Observe: if we thought every number as node, and every pair as an edge
 * 	We end up with a graph that is an undirected chain
 * 	[1-2-3-4-5]
 *
 * 	This means there are 2 possible arrays: [1, 2, 3, 4, 5]  or [5, 4, 3, 2, 1]
 *
 * 	So all what we need to do is to build the graph and finds the chain begin!
 *
 * 	With a simple observation, we can find one of the begins (1 or 5) trivially
 * 	Simple, each node will have 2 neighbors, except 1 or 5. Each will have a single neighbor only
 *
 *
 * 	As the node values are huge, NOT [0, n-1] range, we will use graph based on hash table
 */

// Tip: we can implement this code without visited. We can always do that on trees/chains using parent info

typedef unordered_map<int, vector<int>> GRAPH;

void add_undirected_edge(GRAPH &graph, int from, int to) {
	graph[from].push_back(to);
	graph[to].push_back(from);
}

void dfs(GRAPH &graph, int node, unordered_set<int> &visited, vector<int> &cc_nodes) {
	visited.insert(node);
	cc_nodes.push_back(node);

	for (int neighbour : graph[node]) {
		if (!visited.count(neighbour))
			dfs(graph, neighbour, visited, cc_nodes);
	}
}

class Solution {
public:
	vector<int> restoreArray(vector<vector<int>> &pairs) {
		int nodes = pairs.size() + 1;
		GRAPH graph;

		// Build graph edges
		for (auto &pair : pairs)
			add_undirected_edge(graph, pair[0], pair[1]);

		unordered_set<int> visited;
		vector<int> cc_nodes;

		for (auto &node_adj : graph) {
			if (node_adj.second.size() == 1) {
				dfs(graph, node_adj.first, visited, cc_nodes);
				break;
			}
		}
		return cc_nodes;
	}
};

int main() {

	return 0;
}
