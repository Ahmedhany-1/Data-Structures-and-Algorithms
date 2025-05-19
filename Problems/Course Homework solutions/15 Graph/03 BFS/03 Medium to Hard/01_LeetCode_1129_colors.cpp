// https://leetcode.com/problems/shortest-path-with-alternating-colors/

#include<iostream>
#include<vector>
#include<queue>
using namespace std;

/*
 * The key idea here, the graph is NOT N nodes, it 2N nodes
 * Specifically, each node is
 * 		One of the N nodes ( to N-1 idx)
 * 		A color: red or blue
 *
 * When a node is not a single value, we may call it a state
 * So the graph has N states, each state is idx and color
 *
 * The best way to work on states is to keep them as states,
 * 		e.g. don't covert to full explicit graph of 2N nodes
 *
 * Now, the task is pretty direct. Do bfs on this N states (or 2N nodes) graph and compute shortest path
 *
 * To work on the states: the queue is queue of states (idx, color)
 * 		Similarly, the visited array is N*2 cells
 *
 * Edge (y, z) exists IFF its color is different from the used color on edge (x, y)
 *
 * Take home lessons:
 * 		This is a state graphs: so each node has several sub-elements
 * 		Think how to generate the neighbor states from the current state
 */

const int OO = 10000000;	// A big value expressing infinity
const int RED = 0;
const int BLUE = 1;

struct edge {
	int to;
	int color;
};

typedef vector<vector<edge>> GRAPH;

void add_directed_edge(GRAPH &graph, int from, int to, int color) {
	graph[from].push_back( { to, color });
}

vector<int> bfs(GRAPH &adjList, int start) {
	int nodes = adjList.size();
	vector<int> answer(nodes, -1);
	vector<vector<int>> len(nodes, vector<int>(2, OO));	// N*2 grid
	queue<edge> q;

	q.push( { start, RED });
	q.push( { start, BLUE });
	len[start][RED] = len[start][BLUE] = 0;
    answer[start] = 0;

	for (int level = 0, sz = q.size(); !q.empty(); ++level, sz = q.size()) {
		while (sz--) {
			int cur = q.front().to, color = q.front().color;
			q.pop();
			for (edge e : adjList[cur])
				if (color != e.color && len[e.to][e.color] == OO) {
					q.push(e);
					len[e.to][e.color] = level + 1;
                    if(answer[e.to] == -1)	// we can reach the node from 2 colors. Keep the first only
					    answer[e.to] = level + 1;
				}
		}
	}
	return answer;
}

class Solution {
public:
	vector<int> shortestAlternatingPaths(int n, vector<vector<int>> &red_edges, vector<vector<int>> &blue_edges) {
		GRAPH adjList(n);

		for (auto &e : red_edges)
			add_directed_edge(adjList, e[0], e[1], RED);

		for (auto &e : blue_edges)
			add_directed_edge(adjList, e[0], e[1], BLUE);

		return bfs(adjList, 0);

	}
};
int main() {

	return 0;
}

