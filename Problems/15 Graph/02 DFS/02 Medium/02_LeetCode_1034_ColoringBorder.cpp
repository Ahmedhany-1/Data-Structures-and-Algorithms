// https://leetcode.com/problems/coloring-a-border/


#include<iostream>
#include<vector>
using namespace std;

/*`
 * We can implement this approach in several ways, but you might do several bugs.
 *
 * Here is a 'safe' approach
 *
 * 1) Perform the normal reachability DFS on a matrix
 * 		Don't update the matrix. Only visited array updated
 *
 * 2) Perform a simple iterative code that check if every node is boundary or not
 * 		1) It must be visited during dfs
 * 		2) Either one of its neighbors is out of the grid
 * 		3) Or an existing neighbor that is NOT part of the CC
 */

class Solution {
private:
	int dr[4] { -1, 0, 1, 0 };
	int dc[4] { 0, 1, 0, -1 };

public:
	// Return true if this position INSIDE the 2D grid
	bool isvalid(int r, int c, vector<vector<int>> &grid) {
		if (r < 0 || r >= (int) grid.size())
			return false;
		if (c < 0 || c >= (int) grid[0].size())
			return false;
		return true;
	}
	void dfs(int r, int c, vector<vector<int>> &grid, vector<vector<bool>> &visited, int oldcolor) {
		if (!isvalid(r, c, grid) || visited[r][c] || grid[r][c] != oldcolor)
			return;

		visited[r][c] = 1;
		for (int d = 0; d < 4; ++d)
			dfs(r + dr[d], c + dc[d], grid, visited, oldcolor);
	}

	void createBoundries(vector<vector<int>> &grid, vector<vector<bool>> &visited, int newColor) {
		int rows = grid.size(), cols = grid[0].size();

		for (int r = 0; r < rows; ++r) {
			for (int c = 0; c < cols; ++c) {
				for (int d = 0; d < 4; ++d) {
					if(!visited[r][c])
						continue;	// NOT part of the CC
					int nr = r + dr[d], nc = c + dc[d];
					if (!isvalid(nr, nc, grid) || !visited[nr][nc])
						grid[r][c] = newColor;	// Boundary
				}
			}
		}
	}

	vector<vector<int>> colorBorder(vector<vector<int>> &grid, int sr, int sc, int newColor) {
		vector<vector<bool>> visited(grid.size(), vector<bool>(grid[0].size()));
		dfs(sr, sc, grid, visited, grid[sr][sc]);
		createBoundries(grid, visited, newColor);
		return grid;
	}
};

int main() {

	return 0;
}
