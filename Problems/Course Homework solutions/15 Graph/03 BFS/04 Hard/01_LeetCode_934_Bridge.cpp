// https://leetcode.com/problems/shortest-bridge

#include<iostream>
#include<vector>
#include<queue>
#include<set>
#include<unordered_set>
#include<unordered_map>
using namespace std;

/*

Imagine we have 100 x 100 matrix
 Inside it 2 filled blocks 10x10 of 1s that are far away from each other

 Logically, the the smallest number of 0s that must be flipped to connect them are
 only between the "boundaries" of the 2 islands
 In a 10x10 grid, we have M = 2*10+2*8 cells at its boundary

 So one brute force idea is as following
 1) Find the 2 islands. Find their boundaries (we did before)
 2) For each pair of cells, one from each island, do BFS to find the shortest distance
 3) This means we did M^2 BFS calls

 Can we improve? Yes, let's use Mutli-src BFS
 Let your queue has all the cells from island1:
 Now per cell in island2, run a single Multi-src BFS to find this cell
 This means we did M BFS calls

 Can we do better? Yes: Multi-src Multi-destination BFS
 Let your queue has all the cells from island1
 Run a single BFS to find the first cell from island2

 Let's simplify coding. Do we really need the boundaries of island1?
 We can simply, add all island1 in the queue
 These cells are visited cells. So, non-boundaries cells anyway can't add neighbors

 Coding:
 1) DFS to find 1 island. Let's color it with 2. Add all values in the queue
 2) Run a normal single BFS from these multi-sources
 	 3)  let's use the same matrix as visited grid
 	 	 Now cell values are: 2 for island1, 1 for island2, 0 for cells to flip
 	 	 When we meet a new cell, let's mark it with 3  (0 flipped to 3)
 	 	 Once you find a 1, this is the smallest number of steps


Take home message. There are 3 variants of BFS:
	1-1: Single Source Single Designation
	M-1: Multi-Source Single Designation
	M-M: Multi-Source Multi-Designation

	All of these variants are a single BFS execution, so the same time complexity
*/

class Solution {
	queue<vector<int>> q;
	int dr[4] { -1, 0, 1, 0 };
	int dc[4] { 0, 1, 0, -1 };

	bool isvalid(int r, int c, vector<vector<int>> &matrix) {
		return r >= 0 && r < (int) matrix.size() && c >= 0 && c < (int) matrix[0].size();
	}
	void dfs(int r, int c, vector<vector<int>> &matrix, int oldcolor = 1, int newcolor = 2) {
		matrix[r][c] = newcolor;
		q.push( { r, c });		// Add q initial starting points

		for (int d = 0; d < 4; ++d) {
			int nr = r + dr[d], nc = c + dc[d];
			if (!isvalid(nr, nc, matrix) || matrix[nr][nc] != oldcolor)
				continue;
			dfs(nr, nc, matrix, oldcolor, newcolor);
		}
	}
public:

	int shortestBridge(vector<vector<int>> &matrix) {
		// Find 1 CC (island): Mark with color 2 and add to the queue
		for (int r = 0; r < (int) matrix.size() && q.empty(); r++)
			for (int c = 0; c < (int) matrix[0].size(); c++)
				if (matrix[r][c] == 1) {
					dfs(r, c, matrix);
					break;
				}
		// Always use sz = q.size(): works for single or multi-src
		for (int level = 0, sz = q.size(); !q.empty(); ++level, sz = q.size()) {
			while (sz--) {
				int r = q.front()[0], c = q.front()[1];
				q.pop();

				for (int d = 0; d < 4; ++d) {
					int nr = r + dr[d], nc = c + dc[d];
					if (!isvalid(nr, nc, matrix) || matrix[nr][nc] == 2 || matrix[nr][nc] == 3)
						continue;

					if (matrix[nr][nc] == 1) 	// bridged
						return level;
					q.push( { nr, nc });
					matrix[nr][nc] = 3;	// Cell with zero. Let's add here bridge (3)
				}
			}
		}
		return -1;
	}
};


int main() {
	vector<vector<int>> matrix {{0, 1}, {1, 0}};
	Solution s;
	s.shortestBridge(matrix);

	return 0;
}

