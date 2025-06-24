// https://leetcode.com/problems/number-of-dice-rolls-with-target-sum/

#include <iostream>
#include <vector>
#include <cstring>
#include <climits>
#include <cassert>
using namespace std;

/*

 For each index, brute force all possible faces and move to the next index

 */

const int MAX_DICES = 30;
const int MAX_TARGET = 1000 + 1;
int memory[MAX_DICES][MAX_TARGET];

const int MOD = 1000000007;
int dices, faces;

int count_combs(int idx, int target) {
	if (target < 0)
		return 0;	// invalid

	if (idx == -1 && target == 0)
		return 1;	// all dices done and target is achieved

	if (idx == -1 || target == 0)
		return 0;	// still more to finish

	auto &ret = memory[idx][target];
	if (ret != -1)
		return ret;

	ret = 0;
	for (int f = 1; f <= faces; f++) {
		ret += count_combs(idx - 1, target - f);
		ret %= MOD;	// early reduce the range
	}
	return ret;
}

class Solution {
public:
	int numRollsToTarget_rec(int n, int k, int target) {
		dices = n, faces = k;
		memset(memory, -1, sizeof(memory));
		return count_combs(dices - 1, target);
	}

	int ans(int idx, int target) {
		if (target < 0)
			return 0;	// invalid

		if (idx == -1 && target == 0)
			return 1;	// all dices done and target is achieved

		if (idx == -1 || target == 0)
			return 0;	// still more to finish

		return memory[idx][target];
	}

	int numRollsToTarget(int dices, int faces, int target_) {
		for (int idx = 0; idx < dices; ++idx) {
			for (int target = 0; target <= target_; ++target) {
				int ret = 0;
				for (int f = 1; f <= faces; f++) {
					ret += ans(idx - 1, target - f);
					ret %= MOD;	// early reduce the range
				}
				memory[idx][target] = ret;
			}
		}
		return ans(dices-1, target_);
	}
};

int main() {

	return 0;
}
