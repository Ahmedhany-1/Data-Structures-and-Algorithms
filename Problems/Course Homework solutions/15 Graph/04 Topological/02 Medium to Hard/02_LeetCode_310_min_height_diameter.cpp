// https://leetcode.com/problems/minimum-height-trees/

#include<iostream>
#include<vector>
#include<queue>
#include<unordered_map>
using namespace std;

/*

Hint: What is the relationship of this problem and the tree diameter?

Any tree has several paths, some of them are diameters.
Thinking of roots from a normal path vs a diameter path, intuitively, 
   diameter will be the one enlarging the tree height!

Assume a tree is a single chain: [1-2-3-4-5], what is the answer?
	Clearly the center, which is 3

Assume a tree is a single chain: [1-2-3-4-5-6], what is the answer?
	Clearly the center, which is 3, 4

The interesting here: the median of the list is the key for a shorter height
 	For an odd list, it is just the middle. Otherwise, we need the 2 middle values

What if the graph has several diameters?
We can show that the number of centroids in a tree is 1 or 2
	Play with examples to convince yourself that even if we have multiple diameters


Single Centroid Case: Suppose a tree has a single centroid. This would mean that removing this 
node divides the tree into subtrees, none of which has more nodes than half the total number 
of nodes in the original tree. This situation arises when the tree is somewhat symmetric or balanced.

proof insigths:

Two Centroids Case: If a tree has two centroids, then they must be adjacent.
 
Removing these two nodes would divide the tree into subtrees, where again, 
none has more nodes than half the total number of nodes. This situation often
occurs in a tree that is 'almost' symmetric but has 
a 'central' edge where if you cut, both sides are nearly equal.

Why Not More Than Two Centroids?: More than two centroids is not possible because 
if there were three or more centroids, 
removing any one of them would still leave a subtree with more than half of 
the total number of nodes. 
This would contradict the definition of a centroid.

Intuitive Understanding: The centroid(s) of a tree is (are) the point(s) that are 'central' 
in terms of the distribution of nodes. 
This centrality ensures that the removal of the centroid node(s) does not leave a 
disproportionately large subtree.

In summary, the structural properties of trees and the definition of centroids lead to 
the conclusion that a tree can have 
either one centroid (in more symmetric cases) or two centroids 
(in nearly symmetric cases with a central edge dividing the tree into almost equal halves).


*/

typedef vector<vector<int>> GRAPH;

void add_undirected_edge(GRAPH &graph, int from, int to) {
	graph[from].push_back(to);
	graph[to].push_back(from);
}
// Return the farthest node and the parent relations
pair<int, vector<int>> bfs(GRAPH &adjList, int start) {
	const int OO = 10000000;	// A big value expressing infinity
	vector<int> len(adjList.size(), OO);
	vector<int> parent(adjList.size(), -1);
	queue<int> q;
	q.push(start);
	len[start] = 0;

	int cur = 0, level = 0, sz = 1;
	for (; !q.empty(); ++level, sz = q.size()) {
		while (sz--) {
			cur = q.front();
			q.pop();
			for (int neighbour : adjList[cur])
				if (len[neighbour] == OO) {	// never visited
					q.push(neighbour);
					len[neighbour] = level + 1;
					parent[neighbour] = cur;
				}
		}
	}
	return {cur, parent};
}

void build_path(vector<int> &parent, int cur_node, vector<int> &path) {
	if (cur_node == -1)
		return;
	build_path(parent, parent[cur_node], path);
	path.push_back(cur_node);
}

vector<int> treeDiam(GRAPH &graph) {
	auto p1 = bfs(graph, 0);			// Get farthest node from 0
	auto p2 = bfs(graph, p1.first);		// Get farthest node from this farthest node
	vector<int> diameter;
	build_path(p2.second, p2.first, diameter);
	return diameter;
}

class Solution {
public:
	vector<int> findMinHeightTrees(int n, vector<vector<int>> &edges) {
		GRAPH graph(edges.size() + 1);

		for (auto &edge : edges)
			add_undirected_edge(graph, edge[0], edge[1]);

		vector<int> diameter = treeDiam(graph);
		int sz = diameter.size();

		if (sz % 2 == 1)
			return {diameter[sz/2]};
		return {diameter[sz/2], diameter[sz/2-1]};
	}
};

int main() {

	return 0;
}


/*

To prove that we can compute the tree diameter with two Breadth-First Searches (BFS), we must first understand the concepts involved:

Tree Diameter: The diameter of a tree is the longest path between any two nodes in the tree. This path is also known as the longest path or the maximum distance between any pair of nodes.

Breadth-First Search (BFS): BFS is a graph traversal algorithm that starts at a selected node (root) and explores all neighbors at the present depth before moving on to the nodes at the next depth level.

The process to find the tree diameter using two BFS operations is as follows:

Step 1: Perform BFS from Any Node

Start with a BFS from any arbitrary node in the tree. This node is often called the "root" for the purpose of this operation.
The BFS will visit all nodes in the tree and can be used to determine the farthest node from the starting node. This is because BFS explores nodes level by level, and in a tree, the last node visited in BFS is guaranteed to be the farthest from the starting node.
Step 2: Perform BFS from the Farthest Node Found in Step 1

Now, perform a second BFS starting from the farthest node found in Step 1.
Similar to the first BFS, this second BFS will find the farthest node from this new starting point.
Why Does This Work?

The key idea here is that the farthest node from any given node in a tree lies at one of the ends of the tree's diameter. This is because if there were a longer path than the one found, it would mean that the initial BFS did not find the farthest node, which contradicts the BFS algorithm that explores all nodes.
Thus, the second BFS, starting from one end of the diameter, will necessarily find the other end of the diameter, as it is the farthest point from the starting node.
Proof by Contradiction

Suppose the method does not give the diameter. Then there must be a longer path between two nodes in the tree than the one we found.
However, this would mean that the first BFS did not find the farthest node from the starting node, or the second BFS did not find the farthest node from the node found in the first BFS. Both cases contradict the nature of BFS in a tree, where the last node visited is the farthest.
Therefore, by using two BFS operations as described, we can reliably compute the diameter of a tree.


*/















