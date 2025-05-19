// https://leetcode.com/problems/shortest-path-to-get-food

#include<iostream>
#include<vector>
#include<queue>
using namespace std;

/*
Straight forward. Just apply BFS on matrix, like dfs on matrix

Once you found food cell, return its level
*/

const int OO = 10000000;	// A big value expressing infinity

// Delta for: up, right, down, left
int dr[4] { -1, 0, 1, 0 };
int dc[4] { 0, 1, 0, -1 };

bool isvalid(int r, int c, vector<vector<char>> &matrix) {
	if (r < 0 || r >= (int) matrix.size())
		return false;
	if (c < 0 || c >= (int) matrix[0].size())
		return false;
	return true;
}

struct cell {
	int r, c;
};

int bfs(vector<vector<char>> &matrix, cell start) {
	vector<vector<bool>> visited(matrix.size(), vector<bool>(matrix[0].size()));
	queue<cell> q;

	q.push(start);
	visited[start.r][start.c] = 1;

	for (int level = 0, sz = q.size(); !q.empty(); ++level, sz = q.size()) {
		while (sz--) {
			int r = q.front().r, c = q.front().c;
			q.pop();

			for (int d = 0; d < 4; ++d) {
				int nr = r + dr[d], nc = c + dc[d];
				if (!isvalid(nr, nc, matrix) || visited[nr][nc] || matrix[nr][nc] == 'X')
					continue;

				if (matrix[nr][nc] == '#')
					return level + 1;

				q.push( { nr, nc });
				visited[nr][nc] = 1;
			}
		}
	}
	return -1;
	// Tip: we can use the matrix itself to mark visited by setting matrix[nr][nc] = 'X';
	// This is good for competitions, but not industry / interviews
}

class Solution {
public:
	int getFood(vector<vector<char>> &matrix) {
		cell start;
		for (int i = 0; i < (int)matrix.size(); i++)
			for (int j = 0; j < (int)matrix[0].size(); j++)
				if (matrix[i][j] == '*')
					start = { i, j };
		return bfs(matrix, start);
	}
};

int main() {

	return 0;
}

