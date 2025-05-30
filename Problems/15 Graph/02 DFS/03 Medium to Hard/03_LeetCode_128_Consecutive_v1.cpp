// https://leetcode.com/problems/longest-consecutive-sequence/

#include<iostream>
#include<vector>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
using namespace std;

/*
 *
 * How a consecutive set of numbers represent a graph?
 * Assume we have numbers: [1, 2, 3, 4, 5]
 * We have 4 edges (1, 2), (2, 3), (3, 4), (4, 5)
 *
 * We will take the array and build its undirected graph as following
 * 	For any pair of values (val, val+1), then we have an edge
 *
 *  How to do that efficiently?
 *  	First, create hashset of the values for easy lookup
 *  	then iterate on the values
 *  		For a given val, check if val+1 exists. If so add an edge
 *
 *
 *  Now, every consecutive group of values is a CC, specifically a chain of nodes
 *  1, 2, 3, 6, 7, 8, 9
 *  	(1, 2), (2, 3)
 *  	(6, 7), (7, 8), (8, 9)
 *
 * Remember: in an undirected chain: only the first and last node has 1 neighbor
 * 	We can use them to find the full chain
 *
 * Be careful from an empty graph, or graph of a single node, or unconnected nodes
 * 	Handle them
 *
 *
 * Be careful from duplicate values: 0 0 0 1 1 1 2 2 2
 * 	We should create a single undirected edge (0, 1) NOT 3
 * 		Otherwise, the chain first value may have several neighbors
 *
 *
 * Overall nice idea, but tricky implementation
 * The non-graph based solutions are safer to code!
 */

typedef unordered_map<int, vector<int>> GRAPH;

void add_undirected_edge(GRAPH &graph, int from, int to) {
	graph[from].push_back(to);
    graph[to].push_back(from);
}

// The graph is chain: 1->2->3->4. We return the chain size
int dfs(GRAPH &graph, int node, unordered_set<int> &visited) {
	visited.insert(node);

	for (int neighbour : graph[node])
		if (!visited.count(neighbour))
			return 1 + dfs(graph, neighbour, visited);
	return 1;	// single last node
}

class Solution {
public:
	int longestConsecutive(vector<int> &nums) {
		// Create hashset of the values to lookup in O(1)
		unordered_set<int> nums_set(nums.begin(), nums.end());

        if(nums_set.size() == 0)
            return 0; // handle empty graph

        // Create undirected edges. If val and val+1 exists, we have an edge
        GRAPH graph;
		for (int val : nums_set) {	// ITERATE on unique values
			if (nums_set.count(val + 1))
				add_undirected_edge(graph, val, val + 1);
		}

		// Find the CCs. Maximize over the CC size
		int mx_cc_size = 1;  // value 1 = handle graph of separate values  [10, 20, 30]
		unordered_set<int> visited;

		for (auto &node_adj : graph) {
			if (!visited.count(node_adj.first) && node_adj.second.size() == 1) {
				int cc_size = dfs(graph, node_adj.first, visited);
				mx_cc_size = max(mx_cc_size, cc_size);
			}
		}
		return mx_cc_size;
	}
};

int main() {

	return 0;
}
