// https://leetcode.com/problems/partition-equal-subset-sum/

#include <iostream>
#include <vector>
#include <cstring>
#include <climits>
#include <cassert>
#include <numeric>	// std::accumulate
using namespace std;

/*

- Observe: the sum of the values must be even, otherwise no way to split
- Assume the sum is 20. This means we need 2 groups each is sum to 10
- Then, if we can find a group, this implies there is another group
- Which is a simple problem, the subset sum problem!
- Reductions is a great tool in solving hard problems


 */

const int MAX_N = 200;
const int MAX_T = 100*200 + 1;
int memory[MAX_N][MAX_T];

vector<int> numbers;

bool can_subset_sum(int idx, int target) {
	// Common habit: cancel first invalid states
	if (target < 0)
		return false;

	if (target == 0)
		return true;	// Critical to handle first

	if (idx == (int) numbers.size())
		return 0;		// can't find combination

	auto &ret = memory[idx][target];
	if (ret != -1)
		return ret;

	if (can_subset_sum(idx + 1, target))
		return ret = true;	// if leaving do it: perfect

	return ret = can_subset_sum(idx + 1, target - numbers[idx]);
	// we can check before subtracting but nicer way is to check
	// early in the function. Easier for complex coding
}

bool subset_sum(const vector<int> &values, int target) {
	numbers = values;
	memset(memory, -1, sizeof(memory));
	return can_subset_sum(0, target);
}

class Solution {
public:
	bool canPartition(vector<int> &nums) {
		int sum_of_elems = accumulate(nums.begin(), nums.end(), 0);

		if (sum_of_elems % 2 != 0)
			return false;	// logically, numbers sum is even

		return subset_sum(nums, sum_of_elems / 2);
	}
};

int main() {
	return 0;
}
