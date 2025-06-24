// https://leetcode.com/problems/minimum-falling-path-sum/

#include <iostream>
#include <vector>
#include <cstring>
#include <climits>
#include <cassert>
#include <unordered_set>
#include <unordered_map>
using namespace std;

/*
A classical DAG path on grid: 3 choices from a node

As we can start from anywhere in the first row, we BF that and minimize among choices

As we minimize, for an invalid path we should return huge value to be discarded
 */

const int MAX = 100 + 1;
int memory[MAX][MAX];
vector<vector<int>> grid;

int minPathSum(int r, int c) {
	int rows = grid.size(), cols = grid[0].size();

	if (c < 0 || c >= cols)
		return INT_MAX/2;			// invalid: some big value. Watch overflows

	if (r == rows - 1)
		return grid[r][c];	// last row

	auto &ret = memory[r][c];
	if (ret != -1)
		return ret;

	int p1 = minPathSum(r + 1, c - 1);
	int p2 = minPathSum(r + 1, c);
	int p3 = minPathSum(r + 1, c + 1);

	return ret = grid[r][c] + min(min(p1, p2), p3);
}

class Solution {
public:

	int minFallingPathSum(vector<vector<int>> &matrix) {
		grid = matrix;
		memset(memory, -1, sizeof(memory));

		// In the first row: try all possible starts
		int mn = INT_MAX;
		for (int j = 0; j < (int)grid.size(); j++)
			mn = min(mn, minPathSum(0, j));
		return mn;
	}
};

int main() {

	return 0;
}
