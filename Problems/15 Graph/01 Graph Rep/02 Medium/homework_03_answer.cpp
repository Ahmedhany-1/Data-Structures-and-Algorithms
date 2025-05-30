#include<iostream>
#include<vector>
using namespace std;

// As the graph is sparce, we better use adjaceny list (or set)
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

// true if this location inside the matrix
bool isValid(int nr, int nc, int rows, int cols) {
	if (nr < 0 || nr >= rows || nc < 0 || nc >= cols)
		return false;
	return true;
}

int main() {
	int rows, cols;

	cin >> rows >> cols;

	GRAPH graph(rows * cols);	

	int nr, nc, to;
	for (int r = 0; r < rows; ++r) {
		for (int c = 0; c < cols; ++c) {
			int from = r * cols + c;

			nr = r + 1, nc = c, to = nr * cols + nc;
			if (isValid(nr, nc, rows, cols))
				add_directed_edge(graph, from, to);

			nr = r - 1, nc = c, to = nr * cols + nc;
			if (isValid(nr, nc, rows, cols))
				add_directed_edge(graph, from, to);

			nr = r, nc = c + 1, to = nr * cols + nc;
			if (isValid(nr, nc, rows, cols))
				add_directed_edge(graph, from, to);

			nr = r, nc = c - 1, to = nr * cols + nc;
			if (isValid(nr, nc, rows, cols))
				add_directed_edge(graph, from, to);
		}
	}
	print_adjaceny_matrix(graph);

	return 0;
}

/*
3 4
Node 0 has neighbors: 4 1
Node 1 has neighbors: 5 2 0
Node 2 has neighbors: 6 3 1
Node 3 has neighbors: 7 2
Node 4 has neighbors: 8 0 5
Node 5 has neighbors: 9 1 6 4
Node 6 has neighbors: 10 2 7 5
Node 7 has neighbors: 11 3 6
Node 8 has neighbors: 4 9
Node 9 has neighbors: 5 10 8
Node 10 has neighbors: 6 11 9
Node 11 has neighbors: 7 10


 */

