// https://leetcode.com/problems/longest-increasing-subsequence/
#include <iostream>
#include <vector>
#include <cstring>
#include <climits>
using namespace std;

vector<int> numList;
const int MAX = 2500 + 1;	// leetcode limit
int memory[MAX];			// let's create once

int LIS(int i) {	// call for each LIS(i)
	if (i == (int) numList.size())
		return 0;

	auto &ret = memory[i];
	if (ret != -1)
		return ret;

	ret = 0;	// Maximize among all valid positions after i
	for (int j = i + 1; j < (int) numList.size(); ++j)
		if (numList[i] < numList[j])
			ret = max(ret, LIS(j));	// take jth position after i

	ret += 1;	// add ith position
	return ret;
}

void LIS_print(int i) {
	if (i == (int) numList.size())
		return;

	// Our definition to the function is to ALWAYS include i
	if (i)	// don't print the dummy value
		cout << numList[i] << " ";

	int optimal = LIS(i);

	for (int j = i + 1; j < (int) numList.size(); ++j)
		if (numList[i] < numList[j]) {
			if (optimal == 1 + LIS(j)) {
				LIS_print(j);
				return;
			}
		}

}

class Solution {
public:
	int lengthOfLIS(const vector<int> &nums) {
		memset(memory, -1, sizeof(memory));
		numList = nums;
		numList.insert(numList.begin(), INT_MIN);

		LIS_print(0);

		int ans = LIS(0) - 1;
		return ans;
	}
};

int main() {
	Solution().lengthOfLIS( { 10, 9, 2, 5, 3, 7, 101, 18 });

	return 0;
}
