// https://leetcode.com/problems/combination-sum-iv/

#include <iostream>
#include <vector>
#include <cstring>
#include <climits>
#include <cassert>
using namespace std;

/*

The key difference with coin-change-2 problem, all valid permutations of an answer is counted

The problem, we used to do pick or leave based on the index, but this enforces an ORDER

To handle that, we simply won't send index any more. Inside the DP, we loop on all the choices

 */

const int MAX_T = 5000 + 1;
int memory[MAX_T];

vector<int> numbers;

int combinationSum(int target) {
	if (target < 0)
		return 0;

	if (target == 0)
		return 1;	// one valid path

	auto &ret = memory[target];
	if (ret != -1)
		return ret;

	// Try all possible choices from here. This way, all permutations are considered
	ret = 0;
	for (auto &value : numbers)
		ret += combinationSum(target - value);

	return ret;
}

class Solution {
public:
	int combinationSum4(vector<int> &nums, int target) {
		numbers = nums;
		memset(memory, -1, sizeof(memory));
		return combinationSum(target);
	}
};

int main() {

	return 0;
}
