// https://leetcode.com/problems/wiggle-subsequence/
#include <iostream>
#include <vector>
#include <cstring>
#include <climits>
#include <algorithm>
using namespace std;

/*
Similar to next-location, we can use the internal LIS loop
Now this is O(N) memory
 */

const int OO = 1e9;

const int MAX = 1000 + 1 + 1;
int memory[MAX][2];
vector<int> nums;

enum states {
	UP, DOWN
};

// Excluding this index that we reached with direction up or dwon, what is the max sequence?
int wiggle(int idx, int direction_to_prev) {
	if (idx == -1)
		return 0;

	auto &ret = memory[idx][direction_to_prev];
	if (ret != -1)
		return ret;

	ret = 0;
	for (int prev = 0; prev < idx; ++prev) {
		if (nums[prev] > nums[idx] && direction_to_prev == DOWN)
			ret = max(ret, 1 + wiggle(prev, UP));

		if (nums[prev] < nums[idx] && direction_to_prev == UP)
			ret = max(ret, 1 + wiggle(prev, DOWN));
	}

	return ret;
}

class Solution {
public:

	int wiggleMaxLength(vector<int> &nums_) {
		nums = nums_;
		memset(memory, -1, sizeof(memory));
		// Mathematically, we need to prove the last number can always be part of an optimal solution
		int a = wiggle((int) nums.size() - 1, UP);
		int b = wiggle((int) nums.size() - 1, DOWN);
		return 1 + max(a, b);	// 1 for the last number
	}
};

int main() {

	return 0;
}
