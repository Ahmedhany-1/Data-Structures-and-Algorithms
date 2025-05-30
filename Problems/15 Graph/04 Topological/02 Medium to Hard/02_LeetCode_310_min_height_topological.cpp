// https://leetcode.com/problems/minimum-height-trees/

#include<iostream>
#include<vector>
#include<queue>
#include<unordered_map>
using namespace std;

/*

We can develop an idea that is inspired from BFS and implemented like a topological sort!

The idea is shrinking (deleting) the tree leaves LEVEL-by-LEVEL
	Undirected tree node will be leave if in-degree = 1

Imagine a chain: 1-2-3-4-5-6-7
	Nodes 1 and 7 are the current chains. Remove them
	2-3-4-5-6
	Next leaves: 2 and 6. Remove (level 2)
	3-4-5
	Next leaves: 3 and 5. Remove (level 3)
	4

	This is for odd length

	For even length: 1-2-3-4-5-6-7-8
	Stop when there are only 2 nodes: 4-5

The same approach for a tree. The proof is intuitive.
	Leave nodes will make the tree height very high
	The centroids somewhere in the tree are affected by these leaves
	if a centroid at height 7, after we remove ALL leaves at current level,
		the this centroid height is decreasing by one

	See editorial figures

Implementation:
	Like topological sort but
		graph is undirected
		the focus on in-degree = 1
		Stop when there are nodes <= 2

 */

typedef vector<vector<int>> GRAPH;

void add_undirected_edge(GRAPH &graph, int from, int to) {
	graph[from].push_back(to);
	graph[to].push_back(from);
}

vector<int> tree_centroids(const GRAPH &adjList) {	// O(V)
	int sz = adjList.size();

	if(sz == 1)		// special case
		return {0};

	vector<int> indegree(sz, 0);
	for (int i = 0; i < sz; ++i)
		for (int j : adjList[i])
			indegree[j]++;

	queue<int> ready;
	for (int i = 0; i < sz; ++i)
		if (indegree[i] == 1)	// leaves
			ready.push(i);

	// keep shrinking leaves: level by level
	while (sz > 2) {
		int level_sz = ready.size();	// how many leaves NOW
		sz -= level_sz;
		while (level_sz--) {	// level by level like BFS
			int i = ready.front();
			ready.pop();

			for (int j : adjList[i])
				if (--indegree[j] == 1)
					ready.push(j);
		}
	}
	vector<int> res;
	while (!ready.empty()) {
		res.push_back(ready.front());
		ready.pop();
	}
	return res;
}

class Solution {
public:
	vector<int> findMinHeightTrees(int n, vector<vector<int>> &edges) {
		GRAPH graph(edges.size() + 1);

		for (auto &edge : edges)
			add_undirected_edge(graph, edge[0], edge[1]);

		return tree_centroids(graph);
	}
};

int main() {

	return 0;
}

