// https://leetcode.com/problems/walls-and-gates/

#include<iostream>
#include<vector>
#include<queue>
using namespace std;



/*
We can brute force this problem by running BFS from every room! Can we do better?

Observe: each room can be connected to one of the nearest gates
		 but each gate can be used by many rooms, if it is their shortest gate

This motivates reverse thinking:
	Don't start from the room to find a SINGLE matching gate (the first nearest)
	Start from the gate to find its distance to each room (1 to many relationship)

Now how can we do this problem in O(ROWS * COL)?

This can be named: multi-source BFS
	In this variant, we have many starting points at the same time (the gates here)
	We simply add them to the queue and run the normal BFS
	So instead of a single start, we add all possible starting

	This means in level 1: each gate find the rooms of 1 step distance
	This means in level 2: each gate find the rooms of 2 steps distance
	And so on
	Hence, the first gate reach a room, then this is its shortest distance

Convenience yourself by tracing some examples
The whole idea, instead of doing one by one, we do them together
The advantage, each cell is marked as visited once.

Take home lesson: If we have multiple starts, we just add them to the queue

 */












const int OO = 2147483647;	// A big value expressing infinity

// Delta for: up, right, down, left
int dr[4] { -1, 0, 1, 0 };
int dc[4] { 0, 1, 0, -1 };

bool isvalid(int r, int c, vector<vector<int>> &matrix) {
	if (r < 0 || r >= (int) matrix.size())
		return false;
	if (c < 0 || c >= (int) matrix[0].size())
		return false;
	return true;
}

struct cell {
	int r, c;
};

void bfs(vector<vector<int>> &matrix) {
	int rows = matrix.size(), cols = matrix[0].size();
	vector<vector<bool>> visited(rows, vector<bool>(cols));
	queue<cell> q;

	// Add all BFS starting points
	for (int r = 0; r < rows; ++r) {
		for (int c = 0; c < cols; ++c)
			if (!matrix[r][c]) {
				q.push( { r, c });
				visited[r][c] = 1;
			}
	}

	for (int level = 0, sz = q.size(); !q.empty(); ++level, sz = q.size()) {
		while (sz--) {
			int r = q.front().r, c = q.front().c;
			q.pop();

			for (int d = 0; d < 4; ++d) {
				int nr = r + dr[d], nc = c + dc[d];
				if (!isvalid(nr, nc, matrix) || visited[nr][nc] || matrix[nr][nc] == -1)
					continue;

				if (matrix[nr][nc] == OO)	// if so, this is the first gate reach me!
					matrix[nr][nc] = level + 1;

				q.push( { nr, nc });
				visited[nr][nc] = 1;
			}
		}
	}
}

class Solution {
public:
	void wallsAndGates(vector<vector<int>> &rooms) {
		bfs(rooms);
	}
};

int main() {

	return 0;
}

