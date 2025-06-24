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
	UP = 0, DOWN = 1
};

class Solution {
public:

	int wiggleMaxLength(vector<int> &nums) {
		// 0 as the definition excludes the current location
		memory[0][UP] = memory[0][DOWN] = 0;

		for (int idx = 1; idx < (int)nums.size(); ++idx) {
			for (int direction_to_prev = 0; direction_to_prev < 2; ++direction_to_prev) {
				int ret = 0;
				for (int prev = 0; prev < idx; ++prev) {
					if (nums[prev] > nums[idx] && direction_to_prev == DOWN)
						ret = max(ret, 1 + memory[prev][UP]);

					if (nums[prev] < nums[idx] && direction_to_prev == UP)
						ret = max(ret, 1 + memory[prev][DOWN]);
				}
				memory[idx][direction_to_prev] = ret;
			}
		}
		int a = memory[(int) nums.size() - 1][UP];
		int b = memory[(int) nums.size() - 1][DOWN];
		return 1 + max(a, b);
	}
};

int main() {

	return 0;
}
