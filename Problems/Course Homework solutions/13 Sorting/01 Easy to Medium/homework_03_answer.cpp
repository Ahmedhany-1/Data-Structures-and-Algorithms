#include<iostream>
#include<vector>
#include<algorithm>
#include<climits>
using namespace std;

/*
 * Out of 2N numbers, N of them will be summed We want to maximize this summation
 *
 * Assume we have the numbers
 * 1, 2, 3, 4, 5, 6, 7, 8
 *
 * In any pair (a, b): we take the minimum.
 * We need to keep the large values as much as we can
 *
 * Let's start with the smallest value: 1
 * min(1,x) = 1. So logically (greedily), we want x to be the
 * smallest among all possible choices
 * so that we leave more bigger values for other pairs
 * The best choice is 2. So pair (1, 2) = 1
 *
 * Now next is 3. Again min(3,x) = 3
 * So again, find the next available min: 4
 *
 * This takes us to easy idea
 * Sort them 1, 2, 3, 4, 5, 6, 7, 8
 * Pair each consecutive values (1,2), (3,4), (5,6), (7,8)
 * Take the minimums: 1+3+5+7
 * 
 * This is a greedy algorithm :)
 */

class Solution {
public:
	int arrayPairSum(vector<int> &nums) {	// O(nlogn) time
		sort(nums.begin(), nums.end());

		int max_sum = 0;
		for (int i = 0; i < (int)nums.size(); i += 2)
			max_sum += nums[i];	// min(num[i], num[i+1]) = num[i]
		return max_sum;
	}
};


int main() {

	return 0;
}

