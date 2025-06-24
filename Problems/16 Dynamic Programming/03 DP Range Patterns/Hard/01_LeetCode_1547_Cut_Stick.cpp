// https://leetcode.com/problems/minimum-cost-to-cut-a-stick/
#include <iostream>
#include <vector>
#include <cstring>
#include <climits>
#include <algorithm>
using namespace std;

const int MAX = 100 + 2 + 1;	// 2 for two extra values we add
int memory[MAX][MAX];

vector<int> cuts;

// Find the best cut in this sorted range, exclusively
int cut(int start, int end) {
	if (start + 1 == end)	// 2 Consecutive points. Nothing in between
		return 0;		// No cuts

	auto &ret = memory[start][end];
	if (ret != -1)
		return ret;

	// For all possible cuts exclusively between range ]start, end[
	ret = INT_MAX;
	for (int split = start + 1; split < end; split++) {
		int left = cut(start, split);	// observe 2 calls: left-right
		int right = cut(split, end);
		int cut_cost = cuts[end] - cuts[start];
		ret = min(ret, left + right + cut_cost);
	}
	return ret;
}

class Solution {
public:
	int minCost(int n, vector<int> &cuts_) {
		cuts = cuts_;
		cuts.push_back(0);
		cuts.push_back(n);
		sort(cuts.begin(), cuts.end());

		memset(memory, -1, sizeof(memory));

		return cut(0, (int) cuts.size() - 1);
	}

};

int main() {
	Solution s;

	return 0;
}
