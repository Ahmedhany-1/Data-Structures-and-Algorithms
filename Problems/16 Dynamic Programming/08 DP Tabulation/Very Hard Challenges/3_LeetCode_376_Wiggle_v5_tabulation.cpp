// https://leetcode.com/problems/wiggle-subsequence/
#include <iostream>
#include <vector>
#include <cstring>
#include <climits>
#include <algorithm>
using namespace std;

/*
 With simple observation, we only depends on the previous index
 So no need to store this far memory!
 */

class Solution {
public:

	int wiggleMaxLength(vector<int> &nums) {	// O(n) time and O(1) memory
		int up = 0, down = 0;

		for (int idx = 1; idx < (int) nums.size(); ++idx) {
			if (nums[idx - 1] > nums[idx])
				down = 1 + up;
			else if (nums[idx - 1] < nums[idx])
				up = down + 1;
		}
		return 1 + max(up, down);
	}
};

int main() {

	return 0;
}
