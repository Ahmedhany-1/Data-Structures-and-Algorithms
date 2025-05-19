// https://leetcode.com/problems/jump-game-iii/

#include<iostream>
#include<vector>
#include<queue>
#include<unordered_set>
using namespace std;

/*
Operation-based problems are very common. So here is the "pattern"

We have some item (number, string, object)
We have an operation to apply to get a new item
Each item is a node. Each valid operation builds a (directed) edge

We may call the graph a state graph (like a state diagram in SWE)
A critical step is to count the total number of states
	- important to understand the complexity
	- We need a visited array

Tip: Sometimes, the total number of states are huge.
	 But as we BFS and stop early, we don't explore all the graph


In this problem, the nodes are indices and each node has 2 neighbors from 2 conversions

The number of states are just O(N), where N = array size

O(N) time and memory

Note: in my coding style, I verify entering elements before adding to the queue
This means, if you need special cases on the start, they must be done on the start node(s)

*/





class Solution {
	bool process(queue<int> &q, vector<bool> &visited, vector<int>& arr, int idx) {
		if (idx < 0 || idx >= (int)visited.size() || visited[idx])
			return false;
		if(arr[idx] == 0)
			return true;
		visited[idx] = true;
		q.push(idx);
		return false;
	}
public:
	bool canReach(vector<int>& arr, int start) {
        if(arr[start] == 0)
            return true;

		vector<bool> visited(arr.size());
		queue<int> q;
		q.push(start);
		visited[start] = 1;

		for (int level = 0, sz = 1; !q.empty(); ++level, sz = q.size()) {
			while (sz--) {
				int idx = q.front();
				q.pop();
					if (process(q, visited, arr, idx + arr[idx]) ||
						process(q, visited, arr, idx - arr[idx]))
						return true;
			}
		}
		return false;
	}
};

int main() {

	return 0;
}

