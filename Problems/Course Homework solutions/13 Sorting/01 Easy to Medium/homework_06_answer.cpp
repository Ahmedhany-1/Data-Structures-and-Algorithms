#include<iostream>
#include<vector>
#include<algorithm>
#include<climits>
using namespace std;

/*
 * - Case 1) Assume that all the array values >= 0
 * it is then the maximum sum
 *
 * What if k = 1? We need to keep the sum maximum
 * So, just get the smallest value and * -1
 *
 * What if k = 2? As an even number, it has no effect
 * 7 * -1 * -1 = 7
 *
 * General odd? As same as 1
 *
 * - Case 2) Assume that some of the values are negative
 * Logically, we want to flip as much as we can
 * Assume K = 1, but we have -10, -2, -1
 * Which one to flip? The smallest -10
 *
 * This logic is enough to develop the approach!
 *
 * First sort them small to large
 * As long as there are negative numbers flip them
 * Other wise: handle case 2. Find the minimum and flip it if the remaining k is odd
 *
 *
 * Code below may be tricky on case 2
 * Assume sum is 5+10+15 = 30
 * Assume k = 1: so we actually need: -5+10+15 = 20
 * This is same as 30 - 2*5 = 20
 *
 * Shorter than your code :P
 * Practice makes perfect :)
 */

class Solution {
public:
	int largestSumAfterKNegations(vector<int> &nums, int k) {
		sort(nums.begin(), nums.end());
		int mn = INT_MAX, sum = 0;

		for (int i = 0; i < (int) nums.size(); i++) {
			if (k && nums[i] < 0)
				k -= 1, nums[i] *= -1;
			sum += nums[i];	// sum updated array
			mn = min(mn, nums[i]);
		}
		if (k % 2)	// Odd K: flip another number: the min
			sum -= 2 * mn;
		return sum;
	}
};


int main() {

	return 0;
}

