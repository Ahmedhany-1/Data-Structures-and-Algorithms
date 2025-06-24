// https://leetcode.com/problems/minimum-swaps-to-make-sequences-increasing/
#include <iostream>
#include <vector>
#include <cstring>
#include <climits>
#include <algorithm>
using namespace std;

/*

Standard binary choice problem. Per index we try to swap or not swap
	But verify the ability to do so. The sequence must remain increasing

The state? We need an index. For the history, we only need to know
if the last pair is swapped or not.

 */

const int OO = 1e9;

const int MAX = 100000 + 1;
int memory[MAX][2];
vector<int> A, B;

// We can use last_pair_swapped to compute last_a, last_b
// A smarter trick is just to pass them
// Note: these variables are not part of the DP state
// it is like f(x, y, 2x+y, y-x)
//		The last 2 variables here are inferred from the other variables

int mnSwaps(int idx, int last_pair_swapped, int last_a = OO, int last_b = OO) {
	if (idx == -1)
		return 0;

	auto &ret = memory[idx][last_pair_swapped];
	if (ret != -1)
		return ret;

	int no_swap = OO;
	if (A[idx] < last_a && B[idx] < last_b)
		no_swap = mnSwaps(idx - 1, false, A[idx], B[idx]);

	int swap = OO;
	if (A[idx] < last_b && B[idx] < last_a)
		swap = 1 + mnSwaps(idx - 1, true, B[idx], A[idx]);

	return ret = min(no_swap, swap);
}

class Solution {
public:

	int minSwap(vector<int> &A_, vector<int> &B_) {
		A = A_, B = B_;
		memset(memory, -1, sizeof(memory));
		return mnSwaps(A.size() - 1, false);
	}
};

int main() {

	return 0;
}
