//https://leetcode.com/problems/detect-cycles-in-2d-grid/

#include<iostream>
#include<vector>
using namespace std;

/*
 * With a simple observation, we can reduce the code to connected components counting problem.
 *
 * When we are at node (r, c) and move to a neighbor, e.g, (r+1, c)
 * 	This neighbor tries to go back to (r, c) creating a trivial cycle
 * 	Or move to a visited node
 *
 * 	To handle this 2 cases, we used the visited array to avoid them
 *
 * 	Now, we want to figure out if there is a cycle.
 * 	The cycle happens if you visited a place you visited before
 * 	BUT, this shouldn't be the node we just come from it (our parent node)
 *
 * 	To handle the code, we just add 2 new parameters: par_r, par_c which is the parent node generated the edge
 * 	When iterating on the neighbors, don't go back to the node's parent
 *
 * 	Now, if a node is visited it must come from a cycle!
 */

class Solution {
private:
	int dr[4] { -1, 0, 1, 0 };
	int dc[4] { 0, 1, 0, -1 };

	bool is_cycle;

public:
	int isvalid(int r, int c, vector<vector<char>> &grid) {
		if (r < 0 || r >= (int) grid.size())
			return false;
		if (c < 0 || c >= (int) grid[0].size())
			return false;
		return true;
	}

	void dfs(int r, int c, vector<vector<char>> &grid, vector<vector<bool>> &visited, 
		char oldColor, int par_r = -1, int par_c = -1) {
		if (!isvalid(r, c, grid) || grid[r][c] != oldColor || is_cycle)
			return;

		if (visited[r][c]) {	// Now, a visit = cycle
			is_cycle = true;
			return;
		}

		visited[r][c] = 1;
		for (int d = 0; d < 4; ++d) {
			int nr = r+ dr[d], nc = c + dc[d];

			if(nr == par_r && nc == par_c)
				continue;	// Don't go back to your parent (fake cycle from undirected edge)
			dfs(nr, nc, grid, visited, oldColor, r, c);
		}
	}

	bool containsCycle(vector<vector<char>> &grid) {
		vector<vector<bool>> visited(grid.size(), vector<bool>(grid[0].size()));
		int rows = grid.size(), cols = grid[0].size();

		for (int r = 0; r < rows; ++r) {
			for (int c = 0; c < cols; ++c) {
				if (!visited[r][c]) {	// New CC
					is_cycle = false;
					dfs(r, c, grid, visited, grid[r][c]);
					if (is_cycle)
						return true;
				}
			}
		}
		return false;
	}
};

int main() {

	return 0;
}
