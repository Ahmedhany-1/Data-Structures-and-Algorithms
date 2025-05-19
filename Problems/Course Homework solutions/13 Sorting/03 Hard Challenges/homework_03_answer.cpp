#include<iostream>
#include<vector>
#include<algorithm>
#include<climits>
using namespace std;

/*
 * We can easily write code
 * while all values NOT equal
 * 	do the process
 *
 * This is called a "simulation" algorithm.
 *
 * Let's do something better
 * When you analyze the problem, you notice the following
 *
 * Assume we have values 50 50 40 30 10 5
 *
 * Each number will be reduced eventually as following
 * 50 => 40 => 30 => 10 => 5
 * 50 => 40 => 30 => 10 => 5
 * 40 => 30 => 10 => 5
 * 30 => 10 => 5
 * 10 => 5
 * Ending up with [5, 5, 5, 5, 5, 5]
 *
 * In other words, every number will be reduced  based on how many UNIQUE numbers less than it.
 * 50 (4 values),50 (4 values), 40 (3 values), 30 (2 values), 10 (1 value)
 *
 * We can build several O(nlogn) approaches to implement that.
 * All of them start by sorting the number from large to small
 *
 * Let me share with you a very smart and short implicit processing to that.
 * It focus on the following idea
 *
 * If we have [9, 9, 9, 9, 7, 5, 3, 1]
 * We know all of these four 9s will be reduced to 7. Why do them separately while we can do them as 1 batch?
 * So reduce the four 9's together to 7           [4 steps]
 * [7, 7, 7, 7, 7, 5, 3, 1]
 * Now reduce the 5 7s at once to 5           [5 steps]
 * [5, 5, 5, 5, 5, 5, 3, 1]
 * Now reduce the 6 5s at once to 3           [6 steps]
 * Now reduce the 7 3s at once to 1           [7 steps]
 *
 * This is called batch processing
 *
 * Coding wise
 * 	when you iterate from large to small, at the ith step (0-based)
 * 	we have i numbers with EQUAL values and will reduce them at once
 * 		E.g. [9, 9, 9, 9, 7, 5, 3, 1]
 * 			at index (4), we have 4 9s to reduce to 7
 * 			at index (5), we have 5 7s to reduce to 3
 *
 * Anyway: code it in whatever way
 *
 * Shorter than your code :P
 */

class Solution {
public:
	int reductionOperations(vector<int> &nums) {
		sort(nums.rbegin(), nums.rend());	// large to small

		int operations = 0;
		for (int i = 1; i < (int)nums.size(); ++i)
			if (nums[i] != nums[i - 1])
				operations += i;	// There are i numbers with value nums[i-1]: reduce to nums[i] value

		return operations;
	}
};

int main() {

	return 0;
}

