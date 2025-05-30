// https://leetcode.com/problems/missing-element-in-sorted-array/
#include<iostream>
#include<vector>
#include<algorithm>
#include<climits>
#include<cmath>
#include<set>
using namespace std;

/*
 * Check out the editorial
 *
 * Assume missing(idx, nums) return how many numbers are missing until nums[idx]
 * 	If missing(5) = 10 values, then missing(6) must be at least 10
 * 	So increasing monotonic function
 *
 * Then, we can binary search over the indices
 * 	Find the first idx where missing(idx) >= k
 * 	With basic logic, we can find the kth number from idx-1
 *
 * How to code missing(idx, nums)?
 * 		Assume the array is [3, 4, 5, 6, 10]
 * 		At index 4, value 10, in the best case we should have
 * 		all values from 3 to 10, which are 10-3+1 = 8 values
 * 		We are at index 4. But we can see, there are 3 values missing: {7, 8, 9}
 * 		Which can be computed from: 10-3-4 = 3
 * 			nums[idx] - nums[0] - idx
 */

class Solution {
public:
	// Return how many numbers are missing until nums[idx]
	int missing(int idx, vector<int> &nums) {
		return nums[idx] - nums[0] - idx;
	}
	// Using idx, what is kth missing number
	int kth(int idx, vector<int> &nums, int k) {
		// k - missing(idx, nums) = the remaining values
		return nums[idx] + k - missing(idx, nums);
	}

	int missingElement(vector<int> &nums, int k) {
		int n = nums.size();
		// kth missing number after last number?
		if (k > missing(n - 1, nums))
			return kth(n - 1, nums, k);

		int start = 0, end = n - 1, lower_bound = -1;
		// find the first idx where missing(idx) >= k
		while (start <= end) {
			int mid = start + (end - start) / 2;

			if (missing(mid, nums) < k)
				start = mid + 1;
			else
				end = mid - 1, lower_bound = mid;
		}
		// Use the previous idx (lower_bound - 1) to find the missing element
		return kth(lower_bound - 1, nums, k);
	}
};

int main() {

	return 0;
}
