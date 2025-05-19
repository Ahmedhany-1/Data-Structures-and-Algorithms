// https://leetcode.com/problems/count-sub-islands/

#include<iostream>
#include<vector>
using namespace std;

/*
 * We can implement this problem in several ways, but here is the most efficient and simplest one
 *
 * We will perform Connected Components DFS procedure in the standard way based on grid2
 * While we find a CC in grid2, we must find its cells are covered in grid1
 * If the whole CC is found in grid2 and its coverage in grid1, then we have a sub-island
 *
 * In code below, I used the grid itself to also mark the visited nodes.
 * 	This is OK, as long as no problem with changing the given arrays
 *
 * O(NM) time and memory
 */

class Solution {
	// Delta for: up, right, down, left
	int dr[4] { -1, 0, 1, 0 };
	int dc[4] { 0, 1, 0, -1 };

	bool is_sub_island;

	// Return true if this position INSIDE the 2D grid2
	bool isvalid(int r, int c, vector<vector<int>> &grid2) {
		if (r < 0 || r >= (int) grid2.size())
			return false;
		if (c < 0 || c >= (int) grid2[0].size())
			return false;
		return true;
	}

public:

	void dfs(int r, int c, vector<vector<int>> &grid1, vector<vector<int>> &grid2) {
		if (!isvalid(r, c, grid2) || grid2[r][c] == 0)
			return;

		if (grid2[r][c] && !grid1[r][c]) {
			is_sub_island = false;	// Grid2 CC still has more cells!
			return;
		}
		grid2[r][c] = 0;	// use the same grid to mark visited

		for (int d = 0; d < 4; ++d)
			dfs(r + dr[d], c + dc[d], grid1, grid2);
	}

	int countSubIslands(vector<vector<int>> &grid1, vector<vector<int>> &grid2) {
		int count = 0;
		for (int r = 0; r < (int) grid2.size(); ++r) {
			for (int c = 0; c < (int) grid2[0].size(); ++c) {
				if (grid2[r][c]) {	// A new CC in grid2
					is_sub_island = true;
					dfs(r, c, grid1, grid2);
					count += is_sub_island;
				}
			}
		}
		return count;
	}
};

int main() {

	return 0;
}
