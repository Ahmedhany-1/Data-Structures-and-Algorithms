// https://leetcode.com/problems/tree-diameter/
// https://www.spoj.com/problems/PT07Z/

#include<iostream>
#include<vector>
#include<cassert>
using namespace std;

/*
 * Let's create a rooted tree from node(0)
 * This is just the normal dfs from node(0).
 * If we prevent going back to the parent, no need for visited array
 *
 * Let's define height(node) = 1 + longest path from this node to one of its leaf
 * 		If graph is 0 -> 1 -> 3 -> 2
 * 		height(2) = 1, height(3) = 2, height(1) = 3, height(0) = 4
 *
 * This can be trivially computed. Let dfs(node) return its height
 * Then for a node, compute the maximum among all children. return 1 + max
 *
 * So far, this is trivial height you learned in data structures - binary tree
 *
 * ==================
 * The diameter has 1 of 2 cases
 * 1) go through the current node
 * 2) doesn't go through the current node
 *
 * For case 1:
 * 		Assume a node has 4 children and their highest {4, 7, 2, 9}
 * 		The the longest path should go through the longest 2 heights
 * 		so my height is 1 + 7 + 9
 *
 * For case 2:
 * 		Then recursion should find the best diameter for each child
 *
 *
 * The correctness proof is trivial!
 * And we just do a single dfs compare to 2 BFS!
 */

typedef vector<vector<int>> GRAPH;

void add_undirected_edge(GRAPH &graph, int from, int to) {
	graph[from].push_back(to);
	graph[to].push_back(from);
}

int max_diameter_so_far = 0;

int dfs(GRAPH &graph, int node, int parent = -1) {
	int mxHeight1 = 0, mxHeight2 = 0;

	for (int neighbour : graph[node]) {
		if (neighbour == parent)
			continue;

		int h = dfs(graph, neighbour, node);
		if (mxHeight1 < h)
			mxHeight2 = mxHeight1, mxHeight1 = h;
		else if (mxHeight2 < h)
			mxHeight2 = h;
	}
	max_diameter_so_far = max(max_diameter_so_far, mxHeight1 + mxHeight2);
	return 1 + mxHeight1;
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

	max_diameter_so_far = 0;
	dfs(graph, 0);
	cout << max_diameter_so_far << "\n";

	return 0;
}

// For LeetCode
class Solution {
private:
public:
	int treeDiameter(vector<vector<int>> &edges) {
		GRAPH graph(edges.size() + 1);

		for (auto &edge : edges)
			add_undirected_edge(graph, edge[0], edge[1]);

		max_diameter_so_far = 0;
		dfs(graph, 0);
		return max_diameter_so_far;
	}
};
