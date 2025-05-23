#include<iostream>
#include<vector>
using namespace std;

typedef vector<vector<int>> GRAPH;

void add_directed_edge(GRAPH &graph, int from, int to) {
	graph[from].push_back(to);
}

void print_adjaceny_matrix(GRAPH &graph) {
	int nodes = graph.size();
	for (int from = 0; from < nodes; ++from) {
		cout << "Node " << from << " has neighbors: ";
		for (int to = 0; to < (int) graph[from].size(); ++to)
			cout << graph[from][to] << " ";
		cout << "\n";
	}
}

void print_chain(GRAPH &graph, int from) {
	cout << from << " ";

	if (graph[from].size() > 0)
		print_chain(graph, graph[from][0]);
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

	int queries;
	cin >> queries;
	while (queries--) {
		int node;
		cin >> node;
		print_chain(graph, node);
		cout << "\n";
	}
	return 0;
}

/*
6 5
4 1
1 2
5 3
0 5
3 4
4
0
3
1
2


Output
0 5 3 4 1 2
3 4 1 2
1 2
2
 */

