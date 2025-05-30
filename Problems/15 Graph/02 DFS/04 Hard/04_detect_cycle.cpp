// Update: you may use this relevant problem to test your code more
// https://leetcode.com/problems/graph-valid-tree/





#include<iostream>
#include<vector>
using namespace std;

/*
 * Recall:
 * 		A tree is an undirected graph of N nodes and N-1 edges
 * 			Single path from any node to another
 * 			No cycles
 * 			If you added a single edge ==> created a single cycle
 *
 * 		A forest: collection of subtrees. So total #edges <= N-1
 *
 *
 * In fact, the code is almost direct DFS. We already discussed before finding cycle in the matrix
 * 		The whole trick is to add the parent node to dfs parameters we came from to avoid going
 * 		If we visited a visited node, there must be a cycle
 *
 * But is not dfs O(E+V)?
 * For an undirected graph to have no cycles, it must be a forest of at most n-1 edges
 *
 * So now we have 2 cases:
 * 1) Graph is a forest of at most n-1 edges and no cycles
 * 		Clearly: E = O(V). So we are O(V)
 *
 * 2) A general graph of cycles
 * 		Then in the worst case after N edges we must go back to a visited node!
 * 		Imagine simple graph of 5 nodes
 * 		0 -> 1 -> 2 -> 3 -> 4 -> 0
 *
 * So in both cases the algorithm is O(V)
 *
 * Graph properties play a big role in proving different things.
 * DFS has many interesting properties NOT discussed yet by the course
 *
 * What if we have a directed graph. Do the approach work.
 * Consider this simple graph:
 * 	(0, 1), (1, 2), (0, 2)
 * 	Clearly, no cycle.
 *
 * 	DFS starts from 0, move to 1, then move 2
 * 		Now visited are {0, 1, 2}
 * 	DFS recursion goes back to 0 to resume. Visit 2
 * 		But it is visited and cycle? But no cycle!
 *
 * 		As you see, the algorithm fails
 *
 * 		What do you think the reasons for this contradiction?
 * 			Hint: the visited nodes during stack active calls
 *
 */


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

	// Tip: if we know number of edges, then if edges >= n, it must contain cycles
}

int main() {
	//freopen("04_detect_cycle-input.txt", "rt", stdin);
	int cases;
	cin >> cases;

	while (cases--) {
		int nodes, edges;
		cin >> nodes >> edges;

		GRAPH graph(nodes);

		for (int e = 0; e < edges; ++e) {
			int from, to;
			cin >> from >> to;
			add_undirected_edge(graph, from, to);
		}
		if (has_cycle(graph))
			cout << "Yes\n";
		else
			cout << "No\n";
	}

	return 0;
}
