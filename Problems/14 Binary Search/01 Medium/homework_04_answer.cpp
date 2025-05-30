#include<iostream>
#include<vector>
#include<algorithm>
#include<climits>
#include<cmath>
using namespace std;

class Solution {
public:
	// Given a value (represent an interval end): Find the first interval that is its start >= the value
	int BSfindFirst(vector<vector<int>> &startings, int eval) {
		int start = 0, end = (int) startings.size() - 1, position = -1;

		while (start <= end) {
			int mid = start + (end - start) / 2;
			if (startings[mid][0] < eval)	// start < current interval end
				start = mid + 1;
			else if (startings[mid][0] >= eval)	// a possible answer
				end = mid - 1, position = mid;	// Find smaller in left
		}
		return position;
	}

	vector<int> findRightInterval(vector<vector<int>> &interevals) {
		vector<vector<int>> startings;
		for (int i = 0; i < (int) interevals.size(); ++i)
			startings.push_back( { interevals[i][0], i });
		sort(startings.begin(), startings.end());	// sort on unique starts

		vector<int> ans(interevals.size(), -1);
		for (int i = 0; i < (int) interevals.size(); ++i) {
			int idx = BSfindFirst(startings, interevals[i][1]);
			if (idx != -1)
				ans[i] = startings[idx][1];
		}
		return ans;
	}
};

int main() {

	return 0;
}

