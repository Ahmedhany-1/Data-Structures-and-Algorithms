// https://leetcode.com/problems/filling-bookcase-shelves/
#include <iostream>
#include <vector>
#include <cstring>
#include <climits>
#include <algorithm>
#include <cassert>
using namespace std;

/*

Direct Consecutive range pattern
We want to find a good blocks split

dp(idx)
	Try all consecutive ranges as long as total width <= shelfWidth
		For each choice [idx, k] subarray, recurse on the remaining dp(k+1)
		The choice cost is the max height in the subarray [idx, k]

 */

const int MAX = 1000 + 1;
int memory[MAX];

vector<vector<int>> books;
int shelfWidth;

int arrange(int idx) {
	if (idx >= (int) books.size())
		return 0;

	auto &ret = memory[idx];
	if (ret != -1)
		return ret;
	ret = INT_MAX;
	int total_width = 0, mx_height = 0;

	for (int k = idx; k < (int) books.size(); k++) {
		total_width += books[k][0];
		mx_height = max(mx_height, books[k][1]);

		if (total_width > shelfWidth)
			break;
		ret = min(ret, mx_height + arrange(k + 1));
	}
	return ret;
}

class Solution {
public:
	int minHeightShelves(vector<vector<int>> &books_, int shelfWidth_) {
		books = books_;
		shelfWidth = shelfWidth_;
		memset(memory, -1, sizeof(memory));
		return arrange(0);
	}
};
int main() {

	return 0;
}

