// https://leetcode.com/problems/coin-change-2/

#include <iostream>
#include <vector>
#include <cstring>
#include <climits>
#include <cassert>
using namespace std;

/*

Similar to subset sum, we have index and target
	If we don't take item, we move to next with same target
	If we take item, we move to next and subtract from the target

But wait, we want to take the same item several times?
There are 2 approaches:
A) Make an internal loop and keep subtract as much as possible

B) Smart approach: just recurse on the same INDEX again
	Then again it applies leave or take

	Be careful from infinite loops
		As each amount >= 1, we will always move to a smaller state

*/


const int MAX_N = 300+1;
const int MAX_T = 5000 + 1;
int memory[MAX_N][MAX_T];

vector<int> numbers;

int count_conins_change(int idx, int target) {
	if (target < 0)
		return 0;

	if (target == 0)
		return 1;	// one valid path

	if (idx == (int) numbers.size())
		return 0;		// can't find combination

	auto &ret = memory[idx][target];
	if (ret != -1)
		return ret;

	int leave = count_conins_change(idx + 1, target);
	// Use index to allow picking 0 or many items
	int take = count_conins_change(idx, target - numbers[idx]);

	return ret = leave + take;
}


class Solution {
public:
    int change(int amount, vector<int>& coins) {
    	numbers = coins;
    	memset(memory, -1, sizeof(memory));
    	return count_conins_change(0, amount);
    }
};

int main() {


	return 0;
}
