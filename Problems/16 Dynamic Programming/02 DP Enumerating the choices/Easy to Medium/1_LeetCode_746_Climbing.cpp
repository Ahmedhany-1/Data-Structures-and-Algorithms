// https://leetcode.com/problems/min-cost-climbing-stairs/
#include <iostream>
#include <vector>
#include <cstring>
#include <climits>
#include <algorithm>
#include <cassert>
using namespace std;

/*

Direct basic choices problem.

At any state (idx) we can jump to idx+1 or idx+2. In both cases, we pay cost(idx)

So close to Fibonacci?

 */

const int MAX = 1000 + 1;
int memory[MAX];

vector<int> cost;

int climb(int idx) {
	if (idx >= (int) cost.size())
		return 0;

	auto &ret = memory[idx];
	if (ret != -1)
		return ret;

	return ret = cost[idx] + min(climb(idx + 1), climb(idx + 2));
}

class Solution {
public:
	int minCostClimbingStairs(vector<int> &cost_) {
		cost = cost_;
		memset(memory, -1, sizeof(memory));
		return min(climb(0), climb(1));
	}
};

int main() {

	return 0;
}

