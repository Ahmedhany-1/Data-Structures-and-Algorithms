// https://leetcode.com/problems/parallel-courses/

#include<iostream>
#include<vector>
#include<queue>
#include<unordered_map>
using namespace std;

/*
There are 2 popular problems in graph theory: shortest path and longest path

This problem is about the longest path in DAG (as we return -1 for cycles)
	The longest path problem is NP-hard in general graph (for now think: 
	* solutions are extremely slow)
	but it has efficient solutions for DAG graph

	Remember my advise: always notice the extra properties (general graph vs DAG)

Why is this a longest path problem?
	Because the courses that represents the longest chain of prerequisites 
	* will be the bottleneck to finish the study

Many of the DAG problems can be solved with dynamic programming (DP), 
* which is doable in this problem.

However, a nice chance of topological sort is possible for this problem.

=================

We can develop an idea that is inspired from BFS and implemented like a topological sort!

Imagine in the normal topological sort we have 4 nodes with in-degree 0
	We add to the queue and start to get them one by one

What if we did like BFS level by level strategy? Processed the queue exactly 4 times?
	We removed one level of the tree!
	The queue new nodes are the next stage of nodes with in-degree 0!



Take home message
	BFS 			 => Shortest Path in unweighted Graph
	Topological sort => Longest  Path in DAG

*/

typedef vector<vector<int>> GRAPH;

void add_directed_edge(GRAPH &graph, int from, int to) {
	graph[from].push_back(to);
}

int longest_path(GRAPH &adjList) {	// O(E+V)
	int sz = adjList.size();

	vector<int> indegree(sz, 0);
	for (int i = 0; i < sz; ++i)
		for (int j : adjList[i])
			indegree[j]++;

	queue<int> ready;
	for (int i = 0; i < sz; ++i)
		if (indegree[i] == 0)
			ready.push(i);

	// keep shrinking level by level
	int levels = 0, found_nodes = 0;
	while (!ready.empty()) {
		// level by level like BFS
		int level_sz = ready.size();
		while (level_sz--) {
			int i = ready.front();
			ready.pop();
			++found_nodes;

			for (int j : adjList[i])
				if (--indegree[j] == 0)
					ready.push(j);
		}
		++levels;
	}
	if (found_nodes != sz)
		return -1;
	return levels;
}

class Solution {
public:
	int minimumSemesters(int n, vector<vector<int>> &edges) {
		GRAPH graph(edges.size() + 1);

		for (auto &edge : edges)
			add_directed_edge(graph, edge[0]-1, edge[1]-1);

		return longest_path(graph);
	}
};

int main() {

	return 0;
}

