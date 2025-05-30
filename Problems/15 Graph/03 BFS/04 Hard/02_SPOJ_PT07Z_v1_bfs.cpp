// https://leetcode.com/problems/tree-diameter/
// https://www.spoj.com/problems/PT07Z/

#include<iostream>
#include<vector>
#include<queue>
using namespace std;

/*
 * Assume that the tree diameter is between 2 vertices: v1 and v2
 * 		Note: there can be several parts that are diameter.
 * 			Let's pretend there is one only
 *
 * If you are given v1, can you find v2?
 * Yes, a trivial BFS from v1 can tell us one of the farthest nodes from v1 => v2
 *
 * So one simple approach:
 * 	Brute force on all the nodes O(V)
 * 		For each node do BFS on O(E+V)
 * 			So total: O(V * (E+V))
 *
 * Can we do better? Can we find v1 itself in O(E+V)?
 *
 * Claim: If we run BFS from any random node:
 * 	the farthest reachable node is part of the diameter
 *
 * Then the algorithm is:
 * 		1) run bfs from 0.  Let v1 = farthest reachable node from 0
 * 		2) run bfs from v1. Let v2 = farthest reachable node from v1
 * 		3) Diameter is v1-v2
 *
 *
 * Proof? Think about it.
 *  The idea is a bit intuitive but not straight forward to proof
 *
 *  Assume (v1, v2) are the diameter end points.
 *  We start with bfs from some random node k
 *  Consider this 2 cases:
 * 		A) Either k is part of the diameter
 * 			So we have 2 paths: v1 to k and k to v2
 * 				Easily to show one of v1/v2 will be the farthest
 *
 * 		B) k is not on the diameter
 * 			We need to show k must go toward the diameter and end at either v1 or v2
 *
 * Can we find something faster and easier to proof?
 */

typedef vector<vector<int>> GRAPH;

void add_undirected_edge(GRAPH &graph, int from, int to) {
	graph[from].push_back(to);
	graph[to].push_back(from);
}

pair<int, int> bfs(GRAPH &adjList, int start) {
	const int OO = 10000000;	// A big value expressing infinity
	vector<int> len(adjList.size(), OO);
	queue<int> q;
	q.push(start);
	len[start] = 0;

	int cur = 0, level = 0, sz = 1;
	for (; !q.empty(); ++level, sz = q.size()) {
		while (sz--) {
			cur = q.front();
			q.pop();
			for (int neighbour : adjList[cur])
				if (len[neighbour] == OO) {	// never visited
					q.push(neighbour);
					len[neighbour] = level + 1;
				}
		}
	}
	return {cur, len[cur]};	// farthest node and its level
}

int treeDiam(GRAPH &graph) {
	pair<int, int> p1 = bfs(graph, 0);	// Get farthest node from 0
	p1 = bfs(graph, p1.first);			// Get farthest node from this farthest node
	return p1.second;
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

class Solution {
public:
	int treeDiameter(vector<vector<int>> &edges) {
		GRAPH graph(edges.size() + 1);

		for (auto &edge : edges)
			add_undirected_edge(graph, edge[0], edge[1]);

		return treeDiam(graph);
	}
};
