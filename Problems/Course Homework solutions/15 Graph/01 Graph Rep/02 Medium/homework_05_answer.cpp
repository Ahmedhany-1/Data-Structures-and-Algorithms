#include<iostream>
#include<vector>
using namespace std;

typedef vector<vector<int>> GRAPH;

void add_directed_edge(GRAPH &graph, int from, int to) {
	graph[from].push_back(to);
}

void print_paths_len_2(GRAPH &graph) {
	int nodes = graph.size();
	// Iterate on node and get all its neighbor
	// for each neighbor, get its neighbors too
	for (int i = 0; i < nodes; ++i) {
		for (int idx1 = 0; idx1 < (int) graph[i].size(); ++idx1) {
			int j = graph[i][idx1];
			for (int idx2 = 0; idx2 < (int) graph[j].size(); ++idx2) {
				int k = graph[j][idx2];
				cout << i << " " << j << " " << k << "\n";
			}
		}
	}
}

int main() {
	int nodes, edges;
	cin >> nodes >> edges;

	GRAPH graph(nodes);	

	for (int e = 0; e < edges; ++e) {
		int from, to;
		cin >> from >> to;
		add_directed_edge(graph, from, to);
	}
	print_paths_len_2(graph);
	return 0;
}

/*

 6 9
 2 1
 2 5
 2 0
 2 3
 0 5
 1 4
 5 4
 4 3
 4 2

 Output
 0 5 4
 1 4 3
 1 4 2
 2 1 4
 2 5 4
 2 0 5
 4 2 1
 4 2 5
 4 2 0
 4 2 3
 5 4 3
 5 4 2

 */

