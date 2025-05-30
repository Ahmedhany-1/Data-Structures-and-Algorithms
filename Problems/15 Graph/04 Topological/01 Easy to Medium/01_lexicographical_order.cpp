#include<iostream>
#include<vector>
#include<queue>
using namespace std;

/*
The only change, replace the queue with priority queue that picks the smallest first
This way we pick always the smallest one among all current valid choices
 */

typedef vector<vector<int>> GRAPH;

void add_directed_edge(GRAPH &graph, int from, int to) {
	graph[from].push_back(to);
}

vector<int> topsort(const GRAPH &adjList) {	// O(VlogV+E)
	int sz = adjList.size();
	vector<int> indegree(sz, 0);	// compute indegrees of nodes
	for (int i = 0; i < sz; ++i)
		for (int j : adjList[i])
			indegree[j]++;

	priority_queue<int, vector<int>, greater<int> >	ready;	// small to large
	for (int i = 0; i < sz; ++i)
		if (!indegree[i])
			ready.push(i);

	vector<int> ordering;
	while (!ready.empty()) {	// keep picking a ready node
		int i = ready.top();
		ready.pop();
		ordering.push_back(i);

		for (int j : adjList[i])	// remove its outgoing edges
			if (--indegree[j] == 0)	// If a neighbor is ready, add it
				ready.push(j);
	}
	if (ordering.size() != adjList.size())
		ordering.clear();				//There are cycles
	return ordering;
}

int main() {
	//freopen("data.txt", "rt", stdin);
	int cases;
	cin >> cases;

	while (cases--) {
		int nodes, edges;
		cin >> nodes >> edges;

		GRAPH graph(nodes);

		for (int e = 0; e < edges; ++e) {
			int from, to;
			cin >> from >> to;
			add_directed_edge(graph, from, to);
		}
		vector<int> ordering = topsort(graph);

		if (ordering.empty())
			cout << "There is a cycle\n";
		else {
			for (int node : ordering)
				cout << node << " ";
			cout << "\n";
		}
	}
	return 0;
}

/*
3
9 5
4 7
7 1
2 5
5 6
5 3

 9 10
 5 0
 5 7
 6 7
 6 8
 0 1
 7 2
 8 2
 1 2
 2 4
 2 3

 9 11
 5 0
 5 7
 6 7
 6 8
 0 1
 7 2
 8 2
 1 2
 2 4
 2 3
 2 6


0 2 4 5 3 6 7 1 8
5 0 1 6 7 8 2 3 4
There is a cycle

 */
