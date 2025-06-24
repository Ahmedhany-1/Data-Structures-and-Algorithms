// https://leetcode.com/problems/house-robber/
#include <iostream>
#include <vector>
#include <cstring>
#include <climits>
#include <climits>
using namespace std;

/*
 This is a direct pick or leave problem, with 1 constraint to respect
 If you rob house idx, you can't rob at idx+1

 Competitions Coding tips:
 - Use target size + 1, even if no need (just in case you forgot 1-indexing
 - Use baseline with >= and <= rather than ==, as sometimes the index jump in reccurance
 */

const int MAX = 400 + 1;
int memory[MAX];
vector<int> nums;

// Find max profit of robbing starting from this index
int robber(int idx) {
	if (idx >= (int) nums.size())  // careful with jump with +2: use >=
		return 0;

	auto &ret = memory[idx];
	if (ret != -1)
		return ret;

	int skip = robber(idx + 1);
	int rob = nums[idx] + robber(idx + 2);	// jump to valid index, like LIS v2

	return ret = max(skip, rob);
}

class Solution {
public:
	int rob(vector<int> &nums_) {
		nums = nums_;
		memset(memory, -1, sizeof(memory));
		return robber(0);
	}
};

int main() {
	Solution s;

	return 0;
}
