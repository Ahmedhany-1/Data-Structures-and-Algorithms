// https://leetcode.com/problems/out-of-boundary-paths/

#include <iostream>
#include <vector>
#include <cstring>
#include <climits>
#include <cassert>
#include <unordered_set>
#include <unordered_map>
using namespace std;

/*
 * It seems we are counting number of paths on grid that go out the grid boundry
 * But we go in the 4 directions and trivially cycle (infinite)
 * 		dp(r, c)
 *
 * True, but the problem also asks us to do max moves
 * 		So we must add that to the state
 * 		dp(r, c, steps)
 * 		Now, even we can return to the same (r, c)
 * 		we will always have less steps
 *
 * Now code is direct, with careful handling for overflows for C++
 *
 */

const int MOD = 1000000007;

const int MAX = 50 + 1;
int memory[MAX][MAX][MAX];
int rows, cols, max_moves;

int cntWays(int r, int c, int move) {
	if (move == -1)
		return 0;

	if (r < 0 || r >= rows || c < 0 || c >= cols)
		return 1;

	auto &ret = memory[r][c][move];
	if (ret != -1)
		return ret;

	// We can also use directional array
	ret = cntWays(r, c - 1, move - 1);

	ret += cntWays(r, c + 1, move - 1);
	ret %= MOD;	// apply after each step

	ret += cntWays(r + 1, c, move - 1);
	ret %= MOD;

	ret += cntWays(r - 1, c, move - 1);
	ret %= MOD;

	return ret;
}

class Solution {
public:
	int findPaths_rec(int m, int n, int maxMove, int startRow, int startColumn) {
		rows = m, cols = n, max_moves = maxMove;
		memset(memory, -1, sizeof(memory));
		return cntWays(startRow, startColumn, maxMove);
	}

	int ans(int r, int c, int move) {
		if (move == -1)
			return 0;

		if (r < 0 || r >= rows || c < 0 || c >= cols)
			return 1;

		return memory[r][c][move];
	}

	int findPaths(int m, int n, int maxMove, int startRow, int startColumn) {
		// #Moves is the thing that control the state (actual indexing). Must be first loop
		rows = m, cols = n, max_moves = maxMove;

		for (int move = 0; move <= maxMove; ++move) {
			for (int r = 0; r < rows; ++r) {
				for (int c = 0; c < cols; ++c) {

					int ret = ans(r, c - 1, move - 1);
					ret += ans(r, c + 1, move - 1);
					ret %= MOD;
					ret += ans(r + 1, c, move - 1);
					ret %= MOD;
					ret += ans(r - 1, c, move - 1);
					ret %= MOD;
					memory[r][c][move] = ret;
				}
			}
		}
		return ans(startRow, startColumn, maxMove);
	}
};
int main() {

	return 0;
}
