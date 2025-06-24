// https://leetcode.com/problems/dungeon-game/
// https://leetcode.com/problems/dungeon-game/discuss/941108/C%2B%2B-recursion%2B-memorization

#include <iostream>
#include <vector>
#include <cstring>
#include <climits>
#include <cassert>
#include <unordered_set>
#include <unordered_map>
using namespace std;

/*

The hard part of this problem is to think slowly in a logical way

The problem asks for the minHealth, so let's try to define the DP directly based on it

dp(r, c) =  the knight's minimum initial health
			starting from (r, c)
			so that he can rescue the princess at bottom right

			Then the final solution is dp(0, 0)

Basecase
	Assume the matrix is a single value, what is the base case?
		E.g. 7?   	as the value is positive, no health loss. Hence 1 is the answer
		E.g. -7?	To survive, we must be 8  (1 - -7)

Recursion
	Clearly, I can go right or down.
	Let mn = minimum of the health we need start from the right cell or down cell

	Say the mn = 7
	Now let's think in the possible cases for the current cell

	A) Say current cell value is 10:
		Clearly if we started with 1, we take the 10 (11) and cover the 7
			So the answer is 1 if current cell >= mn


	B) Say current cell value is lower than min, e.g. 4
		Then we need to start with 3, so that 3+4 = 7 covers the next path needs
			So 7-4

	C) Say current cell value is lower than min, e.g. -4
		Same as the last case. We need 7 --4 = 11
			Then we cover the loss of -4, and the later 7
*/

const int MAX = 200 + 1;
int memory[MAX][MAX];
vector<vector<int>> matrix;
const int OO = 1e8;

int minHealth(int r, int c) {
	int rows = matrix.size(), cols = matrix[0].size();

	if (r >= rows || c >= cols)	// out of grid
		return OO;	// invalid: use big value for minimization

	if (r == rows - 1 && c == cols - 1) {	// last cell
		if (matrix[r][c] < 0)
			return 1 - matrix[r][c];
		return 1;	// no health loss
	}

	auto &ret = memory[r][c];
	if (ret != -1)
		return ret;

	int mnHealthMove = min(minHealth(r + 1, c), minHealth(r, c + 1));

	if (matrix[r][c] >= mnHealthMove)
		return ret = 1;

	return ret = mnHealthMove - matrix[r][c];
}

class Solution {
public:
	int calculateMinimumHP(vector<vector<int>> &dungeon) {
		matrix = dungeon;
		memset(memory, -1, sizeof(memory));
		return minHealth(0, 0);
	}
};

int main() {

	return 0;
}
