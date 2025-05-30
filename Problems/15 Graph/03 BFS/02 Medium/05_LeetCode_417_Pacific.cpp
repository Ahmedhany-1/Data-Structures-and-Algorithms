// https://leetcode.com/problems/pacific-atlantic-water-flow

#include<iostream>
#include<vector>
#include<queue>
using namespace std;

/*
 The same treatment as walls-and-gates problem

 From the cell perspective: it is like 1-1 relation
 From the ocean perspective: it is 1-M relationship

 This motivates reverse thinking: start from ocean

 The problem is actually 2 parts:
 Is cell reachable from the first row and first column (Pacific)?
 Is cell reachable from the last row and the last column (Atlantic)?

 We solve each one independently, then
 if pacificReachable[i][j] && atlanticReachable[i][j] ==> then consider (i, j) location

 As we have several starting points, this is just  multi-source BFS

 Tip: as we reversed the problem: then cell go to another if src <= targetk
 */

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

void bfs(vector<vector<int>> &matrix, vector<vector<bool>> &visited, vector<cell> &startings) {
	queue<cell> q;

	for (cell &cell : startings) {
		q.push(cell);
		visited[cell.r][cell.c] = 1;
	}

	for (int level = 0, sz = q.size(); !q.empty(); ++level, sz = q.size()) {
		while (sz--) {
			int r = q.front().r, c = q.front().c;
			q.pop();

			for (int d = 0; d < 4; ++d) {
				int nr = r + dr[d], nc = c + dc[d];
				if (!isvalid(nr, nc, matrix) || visited[nr][nc] || matrix[r][c] > matrix[nr][nc]) // > as we reversed
					continue;

				q.push( { nr, nc });
				visited[nr][nc] = 1;
			}
		}
	}
}

class Solution {
public:
	vector<vector<int>> pacificAtlantic(vector<vector<int>> &matrix) {
		int rows = matrix.size(), cols = matrix[0].size();

		vector<vector<bool>> pacificReachable(rows, vector<bool>(cols));
		vector<vector<bool>> atlanticReachable(rows, vector<bool>(cols));

		vector<cell> pacificStartings, atlanticStartings;
		// Get 1st/last row/col as starting points
		for (int r = 0; r < rows; r++) {
			pacificStartings.push_back( { r, 0 });
			atlanticStartings.push_back( { r, cols - 1 });
		}
		for (int c = 0; c < cols; c++) {
			pacificStartings.push_back( { 0, c });
			atlanticStartings.push_back( { rows - 1, c });
		}
		// Compute separately
		bfs(matrix, pacificReachable, pacificStartings);
		bfs(matrix, atlanticReachable, atlanticStartings);
		// Build answers
		vector<vector<int>> results;
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
				if (pacificReachable[i][j] && atlanticReachable[i][j])
					results.push_back( { i, j });

		return results;
	}
};

int main() {

	return 0;
}

