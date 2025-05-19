#include<iostream>
#include<vector>
#include<algorithm>
#include<climits>
using namespace std;

// Editorial: https://leetcode.com/problems/largest-perimeter-triangle/solution/
// time complexity is O(nlogn) - space complexity is O(1)

class Solution {
public:
	int largestPerimeter(vector<int> &nums) {
		sort(nums.rbegin(), nums.rend());	// large to small

		for (int i = 0; i < (int)nums.size() - 2; ++i) {
			// One check is enough as they are sorted. Otherwise 3 validations
			if (nums[i] < nums[i + 1] + nums[i + 2])
				return nums[i] + nums[i + 1] + nums[i + 2];
		}
		return 0;
	}
};

int main() {

	return 0;
}

