// https://leetcode.com/problems/largest-color-value-in-a-directed-graph/

#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
using namespace std;

/*
 * The same logic of problem: https://leetcode.com/problems/parallel-courses-iii/
 *
 * This is a problem where the node want to accumulate information about all the paths under it
 *
 * What do we want to accumulate? the max path frequency per color.
 * Let's create per the node an array of 26 colors
 * Assume a node has the following
 * 	its color is 4
 * 	2 coming edges with: {color 2: freq 7 - color 4: freq 10}   
 *                   	 {color 2: freq 9 - color 4: freq 2     - color 3: freq 5 }
 *
 * 	As a node: all what I care is what is the max path per color:
 * 		So I simply takes the maximum of them
 * 		Hence: {color 2: freq 9 - color 3: freq 5 - color 4: freq 10}
 * 
 * 		As my color is 4, my updated view is:
 * 		Hence: {color 2: freq 9 - color 3: freq 5 - color 4: freq 11}
 *
 *
 * So just process to build that:
 * 		when we pop a node, we increment its color to its array
 *
 * 		then go to each neighbor and update their colors with my colors
 *
 * O(E*C+V) where C = 26
 *
 */

typedef vector<vector<int>> GRAPH;

void add_directed_edge(GRAPH &graph, int from, int to) {
	graph[from].push_back(to);
}

int largestPathColor(const GRAPH &adjList, string &colors) {
	int sz = adjList.size();
	vector<int> indegree(sz, 0);
	for (int i = 0; i < sz; ++i)
		for (int j : adjList[i])
			indegree[j]++;

	queue<int> ready;
	for (int i = 0; i < sz; ++i)
		if (!indegree[i])
			ready.push(i);

	vector<vector<int>> mxColors(sz, vector<int>(26));	// n x 26: 26 colors per node
	int answer = 0, popped_nodes = 0;

	while (!ready.empty()) {
		int i = ready.front(), color = colors[i] - 'a';
		ready.pop();
		++mxColors[i][color];
		++popped_nodes;

		answer = max(answer, mxColors[i][color]);

		for (int j : adjList[i]) {
			if (--indegree[j] == 0)
				ready.push(j);
			// Update my neighbors that I can reach you with this set of colors frequencies
			for (int col = 0; col < 26; ++col)
				mxColors[j][col] = max(mxColors[j][col], mxColors[i][col]);
		}
	}
	if (popped_nodes != sz)
		return -1;
	return answer;
}

class Solution {
public:
	int largestPathValue(string colors, vector<vector<int>> &edges) {
		GRAPH graph(colors.size());

		for (auto &edge : edges)
			add_directed_edge(graph, edge[0], edge[1]);

		return largestPathColor(graph, colors);
	}
};


int main() {

	return 0;
}
