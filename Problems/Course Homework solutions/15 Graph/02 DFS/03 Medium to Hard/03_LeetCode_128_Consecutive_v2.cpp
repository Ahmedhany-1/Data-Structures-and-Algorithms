// https://leetcode.com/problems/longest-consecutive-sequence/

#include<iostream>
#include<vector>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <map>
using namespace std;

/*
 * Here is an interesting observation
 *
 * How to know the chain first value regardless of the graph?
 * Assume we have chain 4, 5, 6, 7
 * 		is 6 the head? No, as 6-1 exists
 * 		is 5 the head? yes, as 5-1 doesn't exist
 *
 * 		In other words, the first number has nothing before it
 *
 * We can even this time create the graph to be directed
 * 		This is not possible in the previous solution
 *
 *
 * Note: for some weird issue, unordered_map in this code fails in LeetCode
 * I spent sometime, and coulnd't know the reason
 * I know maps can invalidate the iterators, but I don't see a reason for that!
 */

//typedef unordered_map<int, vector<int>> GRAPH;
typedef map<int, vector<int>> GRAPH;

void add_directed_edge(GRAPH &graph, int from, int to) {
	graph[from].push_back(to);
}

int dfs1(GRAPH &graph, int node) {
	for (int neighbour : graph[node])
			return 1 + dfs1(graph, neighbour);
	return 1;
}

int dfs(GRAPH &graph, int node) {
    int len = 1;
    while(graph[node].size())
        node = graph[node][0], ++len;
	return len;
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
		for (int val : nums_set) {
			if (nums_set.count(val + 1))
				add_directed_edge(graph, val, val + 1);
		}

		// Find the CCs. Maximize over the CC size
		int mx_cc_size = 1;  // value 1 = handle graph of separate values  [10, 20, 30]

		for (auto &node_adj : graph) {
			if (!nums_set.count(node_adj.first-1)) {	// must be the first value
				int cc_size = dfs(graph, node_adj.first);
				mx_cc_size = max(mx_cc_size, cc_size);
			}
		}
		return mx_cc_size;
	}
};

int main() {
	vector<int> v {-3,2,8,5,1,7,-8,2,-8,-4,-1,6,-6,9,6,0,-7,4,5,-4,8,2,0,-2,-6,9,-4,-1};
	Solution s;
	s.longestConsecutive(v);

	return 0;
}
