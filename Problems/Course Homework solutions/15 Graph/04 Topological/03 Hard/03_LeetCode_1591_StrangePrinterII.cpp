// https://leetcode.com/problems/strange-printer-ii/

#include<iostream>
#include<vector>
#include<queue>
#include<unordered_map>
using namespace std;

/*
In theory, one can think that the initial empty grid is a state (graph node)
	And the target grid is the end goal
	Then we need to develop BFS that tries to go from the start to goal node
		But clearly, this is a very huge graph.
		The way to go is based on more analysis

Observe: Assume we found all locations (r, c) of a specific color,
	then the tightest rectangle of these points can represent its max rectangle
	No logic in coloring beyond this rectangle

Observe: Assume we found the rectangle of each color, and these rectangles don't intersect
	Then we can safely color them in any order

Observe: If rectangle 1 has inside it rectangle 2
	Then we must color 2 before color 1

Observe: If rectangle 1 has inside it rectangle 2, which has inside it rectangle 3
	Then we must color 3 before color 2 which is before color 1

Observe: if rectangle 1 is intersecting with rectangle 2
	Case 1: If rectangle 1 has some cells from rectangle 2 ==> then color 1 then 2
	Case 2: If rectangle 2 has some cells from rectangle 1 ==> then color 2 then 1
	Case 3: if both cases occurs, then this is a cyclic relationship and we can't do it


Building a graph
 Think in each color as a node
 If rectangle i has a cell from color j, then we have directed edge (i, j)

If there is no cycle in this directed graph (DAG), we can color them

An efficient way to know if there is a cycle in a directed graph is topological sort


Take home message: 
 	Topological "ordering" may play a role in problems that require verifying some "ordering"
		Ex: courses prerequistes (lecture), coloring order (here), etc

*/

typedef vector<vector<int>> GRAPH;

void add_directed_edge(GRAPH &graph, int from, int to) {
	graph[from].push_back(to);
}

vector<int> topsort(const GRAPH &adjList) {	// O( E+V )
	int sz = adjList.size();
	vector<int> indegree(sz, 0);	// compute indegrees of nodes
	for (int i = 0; i < sz; ++i)
		for (int j : adjList[i])
			indegree[j]++;

	queue<int> ready;	// add all current nodes that has indegree(0)
	for (int i = 0; i < sz; ++i)
		if (!indegree[i])
			ready.push(i);

	vector<int> ordering;
	while (!ready.empty()) {	// keep picking a ready node
		int i = ready.front();
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

class Solution {
public:
	bool isPrintable(vector<vector<int>> &targetGrid) {
		int rows = targetGrid.size(), cols = targetGrid[0].size();
		int maxColor = 60 + 1;	// let's keep it 1-based

		// For each color, specify its max rectangle: O(R x C)
		vector<int> rmax(maxColor, -1), rmin(maxColor, rows);
		vector<int> cmax(maxColor, -1), cmin(maxColor, cols);
		for (int r = 0; r < rows; r++) {
			for (int c = 0; c < cols; c++) {
				int color = targetGrid[r][c];
				rmax[color] = max(rmax[color], r);
				rmin[color] = min(rmin[color], r);
				cmax[color] = max(cmax[color], c);
				cmin[color] = min(cmin[color], c);
			}
		}
		// For each color: check in its rectangle for other colors
		// If ith rectangle has colors from jth rectangle, then j must be colored first
		// O(Colors x R x C)
		GRAPH graph(maxColor);	
		for (int color = 0; color < maxColor; color++)
			for (int r = rmin[color]; r <= rmax[color]; r++)
				for (int c = cmin[color]; c <= cmax[color]; c++)
					if (targetGrid[r][c] != color)
						add_directed_edge(graph, color, targetGrid[r][c]);
		// O(E+V). V here is the colors.
		return topsort(graph).size() > 0;	// is it DAG? i.e. no cycles in directed graph
	}
};

int main() {

	return 0;
}

