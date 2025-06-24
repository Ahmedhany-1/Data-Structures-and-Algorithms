// https://leetcode.com/problems/partition-array-for-maximum-sum/
#include <iostream>
#include <vector>
#include <cstring>
#include <climits>
#include <algorithm>
#include <cassert>
using namespace std;

/*

Direct consecutive range problem like pearls problem we solved.

The only changes:
- The subarray equation is: length x max
- The subarray's length maximum is k
 */

const int MAX = 500 + 1;
int memory[MAX];

vector<int> arr;
int k;

int partition(int start_idx) {	// O(N^2) time
	if (start_idx >= (int) arr.size())
		return 0;

	auto &ret = memory[start_idx];
	if (ret != -1)
		return ret;

	int mx = INT_MIN;
	ret = INT_MIN;
	// Try all subarrays
	for (int end_idx = start_idx; end_idx < start_idx + k; ++end_idx) {
		if (end_idx >= (int) arr.size())
			break;
		mx = max(mx, arr[end_idx]);
		int len = end_idx - start_idx + 1;
		ret = max(ret, len * mx + partition(end_idx + 1));
	}
	return ret;
}

class Solution {
public:
	int maxSumAfterPartitioning(vector<int> &arr_, int k_) {
		arr = arr_;
		k = k_;
		memset(memory, -1, sizeof(memory));
		return partition(0);
	}
};

int main() {

	return 0;
}

