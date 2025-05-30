// https://leetcode.com/problems/is-graph-bipartite/

#include<iostream>
#include<vector>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <map>
using namespace std;

/*
 * Bipartite graphs are important and with well-known algorithms.
 *
 * This problem is part of a general category of problems we call: Graph Coloring
 * 		We want to color nodes based on some criteria
 * 		A graph is bipartite if and only if it is two-colorable.
 *
 * For a while, it looks scary, but it is actually a direct DFS CC problem!
 *
 * We need to split the nodes to 2 groups. Let's call them color 1 nodes and color 2 nodes
 * 		No edge between 2 nodes of the same color
 *
 * Assume we have chain graph: 0 -> 1 -> 2 -> 3 -> 4
 * Let's start with 0 and color it with 1
 * Now, we are sure its neighbors must be colored with an opposite color (2)
 * 		why? If we colored any neighbor with the same color, then they will belong to the same group!
 * 			But there is an edge between them!
 * 			So logically: node's neighbors must have the opposite color
 *
 * So far: color(0) = 1, color(1) = 2
 *
 * When we move to the neighbor, it will also recurse to color his neighbors with its opposite color
 * Now color (2) = 1, which call to color neighbors with its opposite color
 * Now color (3) = 2, then color (4) = 1
 *
 * Tip: any tree must be bipartite graph
 * Tip: if colors are 1 or 2. Then "3 - color" is always the opposite color (3-1=2, 3-2=1)
 * Tip: Don't assume graph is connected in graph problems!
 * Tip: König's Theorem: If a graph is a bipartite then it has no odd cycles
 */

typedef vector<vector<int>> GRAPH;

class Solution {
private:
	bool is_color_conflict { false };

	void dfs(GRAPH &graph, int node, vector<int> &colors, int assign_color = 1) {
		if (colors[node] == 0)	// NOT visited
			colors[node] = assign_color;
		else {
			if (colors[node] != assign_color)
				is_color_conflict = true;
			return;
		}

		for (int neighbour : graph[node])
			dfs(graph, neighbour, colors, 3 - assign_color);
	}
public:
	bool isBipartite(GRAPH &graph) {
		int nodes = graph.size();
		vector<int> colors(nodes);

		for (int i = 0; i < nodes; ++i) {
			if (colors[i] == 0) {	// New CC
				dfs(graph, i, colors);
				if (is_color_conflict)
					return false;
			}
		}
		return true;
	}
};

int main() {

	return 0;
}
