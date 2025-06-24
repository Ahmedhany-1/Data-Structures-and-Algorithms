// https://leetcode.com/problems/ugly-number-ii/
#include <iostream>
#include <vector>
#include <cstring>
#include <climits>
#include <algorithm>
#include <queue>
using namespace std;

typedef long long ll;

/*

This is a DP-like problem as we incrementally generate ugly numbers from smaller ones

The idea is to simulate the generation, as smart as possible

We start with 1, our base case. Then we generate from it next ugly values
	1*2, 1*3, 1*5			now remove 1

	get minimum 2
		this is the best value to generate the next ugly values
		2*2, 2*3, 2*5

	and so on

	but when we get minimum, we also may have duplicates. To avoid wrong/extra processing, remove them

	Note: we can also use C++ set to force unique values
		https://leetcode.com/problems/ugly-number-ii/discuss/2070482/C%2B%2B-set-solution

Even though, with such duplications, we can do a lot of extra computations
	With more analysis, we can get O(n) solution
		https://leetcode.com/problems/ugly-number-ii/discuss/2104823/C%2B%2B-oror-Easy-oror-Solution-with-Explaination
		The idea is to avoid duplication instead of handling the duplication that happened already
			Directly add the next single ugly value instead of 3 ugly values
 */

class Solution {
public:
	int nthUglyNumber(int n) {
		priority_queue<ll, vector<ll>, greater<ll> > minHeap;

		minHeap.push(1);	// smallest ugly
		int nth = 0;
		ll mnUgly;

		while (!minHeap.empty() && nth < n) {
			nth += 1;
			mnUgly = minHeap.top();	// get min
			// remove all duplicates
			while (!minHeap.empty() && mnUgly == minHeap.top())
				minHeap.pop();

			minHeap.push(mnUgly * 2);
			minHeap.push(mnUgly * 3);
			minHeap.push(mnUgly * 5);
		}
		return mnUgly;
	}
};

int main() {
	cout<<Solution().nthUglyNumber(10);

	return 0;
}
