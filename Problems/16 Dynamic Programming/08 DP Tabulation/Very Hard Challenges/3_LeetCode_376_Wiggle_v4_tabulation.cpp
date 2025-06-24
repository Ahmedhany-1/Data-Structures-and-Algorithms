// https://leetcode.com/problems/wiggle-subsequence/
#include <iostream>
#include <vector>
#include <cstring>
#include <climits>
#include <algorithm>
using namespace std;

/*
 Assume we are at index 30 and now we compare to all previous indices
 Say prev = 10, clearly many values in the middle will make the sequence longer!
 This should be a good signal this loop is unnecessary!

 Let's think about only the previous value
 Say the current index has value 26
 What are the possible relations with the previous value at index-1?
 Smaller e.g. 10 to 26:	so we go UP from previous to this index
 Say the 10 has 2 saves results
 Value 10, DOWN = 4   from sequence 100 15 25 10
 Value 10, UP = 5   from sequence 100 15 25 7 10

 Then memory[idx][UP] can count on this value 10, but which direction? the down
 memory[idx][UP] = 1 + (10, down) = 5 ==> 100 15 25 10 26

 What about memory[idx][DOWN]? We can't extend for this one
 Just use the UP direction with replacement
 memory[idx][DOWN] = (10, up) = 5	==> 100 15 25 7 26	[replace 10 with 26]

 Larger e.g. 30 to 26: so we go DOWN from previous to this index
 Similar logic

 Equal e.g. 26 to 26: so no change!
 If they are equal, we can't extend. Just use with replacement
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

	int wiggleMaxLength(vector<int> &nums) {	// O(n) time and memory
		// 0 as the definition excludes the current location
		memory[0][UP] = memory[0][DOWN] = 0;

		for (int idx = 1; idx < (int) nums.size(); ++idx) {
			int prev = idx - 1;

			if (nums[prev] > nums[idx]) {	// DOWN direction
				memory[idx][DOWN] = 1 + memory[prev][UP];
				memory[idx][UP] = memory[prev][UP];
			} else if (nums[prev] < nums[idx]) {	// UP direction
				memory[idx][UP] = 1 + memory[prev][DOWN];
				memory[idx][DOWN] = memory[prev][DOWN];
			} else {
				memory[idx][UP] = memory[prev][UP];
				memory[idx][DOWN] = memory[prev][DOWN];
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
