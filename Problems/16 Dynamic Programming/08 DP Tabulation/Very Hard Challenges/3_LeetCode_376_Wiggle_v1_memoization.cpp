// https://leetcode.com/problems/wiggle-subsequence/
#include <iostream>
#include <vector>
#include <cstring>
#include <climits>
#include <algorithm>
using namespace std;

/*
This is a standard pick-or-leave problem
Similar to LIS, we need to know the previous number

However, we also need to know what was the direction to this previous number
If the direction was DOWN, then from this previous to this index must be up direction (nums[prev] > nums[idx])

O(N^2) time and memory
 */

const int OO = 1e9;

const int MAX = 1000 + 1;
int memory[MAX][MAX + 1][2];
vector<int> nums;

enum states {
	UP, DOWN
};

int wiggle(int idx, int prev, int direction_to_prev) {
	if (idx == -1)
		return 0;

	auto &ret = memory[idx][prev][direction_to_prev];
	if (ret != -1)
		return ret;

	ret = wiggle(idx - 1, prev, direction_to_prev);	// leave

	// pick if the direction allows it
	if (prev == (int) nums.size() || (nums[prev] > nums[idx] && direction_to_prev == DOWN))
		ret = max(ret, 1 + wiggle(idx - 1, idx, UP));

	if (prev == (int) nums.size() || (nums[prev] < nums[idx] && direction_to_prev == UP))
		ret = max(ret, 1 + wiggle(idx - 1, idx, DOWN));

	return ret;
}

class Solution {
public:

	int wiggleMaxLength(vector<int> &nums_) {
		nums = nums_;
		memset(memory, -1, sizeof(memory));
		return wiggle((int) nums.size() - 1, (int) nums.size(), UP);
	}
};

int main() {

	return 0;
}
