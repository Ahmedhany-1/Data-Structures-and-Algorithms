// https://leetcode.com/problems/maximal-square/

#include <iostream>
#include <vector>
#include <cstring>
#include <climits>
#include <cassert>
#include <unordered_set>
#include <unordered_map>
using namespace std;

/*

Let: max_square_side(r, c): is the side of the largest square containing only 1's and ending at (r, c)
	If we computed it, then the final answer is to iterate on the whole grid and maximizing among all NxM cases

How can we compute max_square_side(r, c)
	Simply, if (r, c) = '0', then no square
	But if 1, imagine the following
		0 0 0 0 0 0
		0 0 0 0 0 0
		0 0 0 1 1 0
		0 0 1 1 1 1
		0 1 1 1 1 1
		0 1 1 1 1 1

		for the last bottom right cell, we can know its max side based on the 3 values: up, left, diagonal
			minimum of these values represents my maximum square + 1 for the bottom right cell
			1 + min(2, 2, 3) = 1 + 2 = 3


Tip: during lectures, I used the opposed definition:
	max_square_side(r, c): is the side of the largest square containing only 1's
		and starting at (r, c) to the bottom right

In the interviews course, we will learn a data-structure based solution for this problem (a harder one)
 */

const int MAX = 300 + 1;
int memory[MAX][MAX];
vector<vector<char>> matrix;

int max_square_side(int r, int c) {
	if (r < 0 || c < 0 || matrix[r][c] == '0')
		return 0;	// invalid or no cell

	auto &ret = memory[r][c];
	if (ret != -1)
		return ret;

	int up = max_square_side(r - 1, c);
	int left = max_square_side(r, c - 1);
	int diagonal = max_square_side(r - 1, c - 1);
	return ret = 1 + min(up, min(left, diagonal));
}

class Solution {
public:
	int maximalSquare(vector<vector<char>> &matrix_) {
		matrix = matrix_;
		memset(memory, -1, sizeof(memory));

		int side = INT_MIN;
		for (int r = 0; r < (int)matrix_.size(); r++)
			for (int c = 0; c < (int)matrix_[0].size(); c++)
				side = max(side, max_square_side(r, c));

		return side * side;
	}
};

int main() {

	return 0;
}
