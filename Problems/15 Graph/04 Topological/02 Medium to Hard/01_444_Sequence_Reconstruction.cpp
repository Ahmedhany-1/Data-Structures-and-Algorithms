// https://leetcode.com/problems/sequence-reconstruction/

#include<i.
0ostream>
#include<vector>
#include<queue>
#include<unordered_map>
using namespace std;

/*
 * We can reduce this problem to a graph as following:
 * Think in every sequence [1, 2, 3, 4] as a directed path: e.g. (1, 2), (2, 3) and (3, 4)
 *
 * Think about the relationship of topological ordering of this graph and the super-sequence:
 * 	The topological graph will:
 * 		have all the graph nodes
 * 		The ordering will respect the paths
 *
 * So all what we need to do:
 * 		Make sure there is a unique topological sort (super-sequence)
 * 
 * 
 * Try to draw cases that will have
 * 	Uniqe sol
 *  Multiple sol
 *
 * We know there can be many topological sort
 * Can we know if there is a SINGLE UNIQE ordering?
 * Yes trivial. The queue MUST always have a single node.
 * 		This means in every step, we can only choose this node
 *
 * So adjust the topological to return empty vector if also there is more than a solution
 * As the vertices are huge AND many values is NOT part of the graph,
 * 	we should use a hash table. So adjust the code for that
 *
 * One bug source, sequences of a single element: e.g. [ [1], [7] ]
 *
 * Note: the org is a permutation with UNIQUE elements.
 * 	Without that, we can't use topological sort, which output UNIQUE values
 *
 * Note: if this problem is only asking if this is a valid super-sequence,
 * 	I think it will be developed similar to LeetCode 792 - Number of Matching Subsequences
 * 	We discuss it later in the interviews course
 *  Think about a non-graph solution for this case
 */


typedef unordered_map<int, vector<int>> GRAPH;

void add_directed_edge(GRAPH &graph, int from, int to) {
	graph[from].push_back(to);
}

/*
 * Update topological sort to work on unordered_map graph
 * Return topological IFF it exists AND unique
 */
vector<int> topsort(GRAPH &adj) {	// O(E+V)
	unordered_map<int, int> indegree;

	for (auto &nodeNeighbours : adj)
		for (int j : nodeNeighbours.second)
			indegree[j]++;

	queue<int> ready;
	for (auto &nodeNeighbours : adj)
		if (!indegree.count(nodeNeighbours.first))
			ready.push(nodeNeighbours.first);

	vector<int> ordering;
	while (!ready.empty()) {
		if (ready.size() > 1)
			return vector<int>();
		int i = ready.front();
		ready.pop();
		ordering.push_back(i);

		for (int j : adj[i])
			if (--indegree[j] == 0)	// If a neighbor is ready, add it
				ready.push(j);
	}
	if (ordering.size() != adj.size())
		return vector<int>();				//There are cycles
	return ordering;
}

class Solution {
public:
	bool sequenceReconstruction(vector<int> &org, vector<vector<int>> &seqs) {
		GRAPH graph(org.size());
		for (auto &seq : seqs) {
			for (int i = 0; i < (int) seq.size() - 1; ++i)
				add_directed_edge(graph, seq[i], seq[i + 1]);
		}
		// special handling for a single value: add them to the graph with no neighbors
		for (auto &seq : seqs) {
			if (seq.size() == 1 && graph.count(seq[0]) == 0)
				graph[seq[0]] = vector<int>();
		}

		vector<int> ordering = topsort(graph);
		return ordering == org;
	}
};

int main() {

	return 0;
}

