#include<iostream>
#include<vector>
#include<unordered_map>
#include<unordered_set>
using namespace std;

/*
 * This is the exact problem as the lecture problem: reachability
 * The only issue: node values are not in range [0, N-1]
 *
 * One nice way to handle that is to use hash_table
 * We use unordered_map to represent the graph (flexible key)
 * We use unordered_set to represent the visited nodes
 *
 * Time complexity is the same.
 * 		This representation is powerful if the graph is very sparse
 * 		such that many nodes are isolated
 * 
 * Be flexible in representing graphs :)
 */

// Adjaceny list, but the keys comes from a hash table
// As the keys in this problem are huge
typedef unordered_map<int, vector<int>> GRAPH;

void add_directed_edge(GRAPH &graph, int from, int to) {
	graph[from].push_back(to);
}

void build_graph_from_edges_list(GRAPH &graph, vector<int> &pid, vector<int> &ppid) {
	for (int i = 0; i < (int) pid.size(); ++i)
		add_directed_edge(graph, ppid[i], pid[i]);
}

void dfs(GRAPH &graph, int node, unordered_set<int> &visited) {
	visited.insert(node);
	for (int neighbour : graph[node])
		if (!visited.count(neighbour))
			dfs(graph, neighbour, visited);
}

vector<int> reachability(GRAPH &graph, int node) {
	unordered_set<int> visited;
	dfs(graph, node, visited);
	return vector<int>(visited.begin(), visited.end());
}

class Solution {
public:
	vector<int> killProcess(vector<int> &pid, vector<int> &ppid, int kill) {
		GRAPH graph;
		build_graph_from_edges_list(graph, pid, ppid);
		return reachability(graph, kill);
	}
};

int main() {

	return 0;
}
