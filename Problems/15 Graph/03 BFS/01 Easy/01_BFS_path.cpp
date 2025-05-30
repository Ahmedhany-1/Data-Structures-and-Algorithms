#include<iostream>
#include<vector>
#include<queue>
using namespace std;

typedef vector<vector<int>> GRAPH;
const int OO = 10000000;	// A big value expressing infinity

void add_directed_edge(GRAPH &graph, int from, int to) {
	graph[from].push_back(to);
}

vector<int> bfs(GRAPH &adjList, int start) {
	vector<int> len(adjList.size(), OO);
	vector<int> parent(adjList.size(), -1);
	queue<int> q;
	q.push(start);
	len[start] = 0;

	for (int level = 0, sz = 1; !q.empty(); ++level, sz = q.size()) {
		while (sz--) {
			int cur = q.front();
			q.pop();
			for (int neighbour : adjList[cur])
				if (len[neighbour] == OO) {	// never visited
					q.push(neighbour);
					len[neighbour] = level + 1;
					parent[neighbour] = cur;
				}
		}
	}
	return parent;
}

void print_path(vector<int> &parent, int cur_node) {
	if (cur_node == -1)
		return;
	print_path(parent, parent[cur_node]);
	cout << cur_node << " ";
}

int main() {
	//freopen("01_BFS_path.txt", "rt", stdin);
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
		int start = 0;
		vector<int> parents = bfs(graph, start);

		for (int i = 0; i < nodes; ++i) {
			if(start == i)
				continue;

			cout << "Path from " << start << " to " << i << ": ";
			if(parents[i] == -1)
				cout<<"Not exist";
			else
				print_path(parents, i);
			cout << "\n";
		}

		cout << "\n";
	}

	return 0;
}


/*
2

5 4
0 1
1 2
2 3
4 3

9 11
1 3
1 5
1 6
3 5
4 3
3 7
5 4
6 0
2 4
2 8
0 2

Path from 0 to 1: 0 1
Path from 0 to 2: 0 1 2
Path from 0 to 3: 0 1 2 3
Path from 0 to 4: Not exist

Path from 0 to 1: Not exist
Path from 0 to 2: 0 2
Path from 0 to 3: 0 2 4 3
Path from 0 to 4: 0 2 4
Path from 0 to 5: 0 2 4 3 5
Path from 0 to 6: Not exist
Path from 0 to 7: 0 2 4 3 7
Path from 0 to 8: 0 2 8
 */
