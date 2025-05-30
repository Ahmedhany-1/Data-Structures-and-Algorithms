// https://leetcode.com/problems/maximum-candies-you-can-get-from-boxes

#include<iostream>
#include<vector>
#include<queue>
#include<set>
#include<unordered_set>
#include<unordered_map>
using namespace std;

/*
This is a simulation problem. As long as you can open a box, open it
	When you open it: you get more keys and more boxes

If a box is a node, and boxes inside build the edges, then this is a graph.
All what we need is to traverse it. The order doesn't matter.
So the more we open, our global status (available keys, which boxes are opened, collected candies) are changed
We can simulate the graph traversal with BFS with multi-src

Tip: make sure to fully understand and trace examples so that you don't create many bugs

Total states? O(n)
*/

class Solution {
private:
	int collected = 0;

	// Add the keys attached to these boxes to available keys
	void addKeysFromBoxes(vector<int> &hasKey, vector<vector<int>> &keys, vector<int> &boxes) {
		for (int box : boxes)
			for (int key : keys[box])
				hasKey[key] = 1;
	}

	void openBoxes(queue<int> &q, vector<bool> &visited, vector<int> &hasKey, vector<int> &candies, vector<int> &boxes) {
		for(int box : boxes) {
			if (!visited[box] && hasKey[box]) {
				q.push(box);
				visited[box] = true;
				collected += candies[box];
			}
		}
	}
public:
	int maxCandies(vector<int> &hasKey, vector<int> &candies, vector<vector<int>> &keys, vector<vector<int>> &containedBoxes, vector<int> &initialBoxes) {
		queue<int> q;
		vector<bool> visited(hasKey.size());
		// Process the initial boxes: add keys and open more boxes
		addKeysFromBoxes(hasKey, keys, initialBoxes);
		openBoxes(q, visited, hasKey, candies, initialBoxes);	// multi-src

		while (!q.empty()) {
			int box = q.front();
			q.pop();
			addKeysFromBoxes(hasKey, keys, containedBoxes[box]);
			openBoxes(q, visited, hasKey, candies, containedBoxes[box]);
		}
		return collected;
	}
};

int main() {

	return 0;
}

