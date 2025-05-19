// https://leetcode.com/problems/heaters/
#include<iostream>
#include<vector>
#include<algorithm>
#include<climits>
#include<cmath>
#include<set>
using namespace std;

/*
 * This is another binary search perspective that just uses lower bound
 *
 * Observe: any house can be covered by the 2 surrounding heaters. Greedily, we don't care about far ones
 * So per house find the closest heater and take the minimum
 * Among all houses needed length, use the maximum
 *
 * Special cases: house before all heaters or after them
 *
 * Implementation: if we sorted heaters, we can lower bound in the array
 *
 * O(nlogn) time
 *
 * Tip: don't stuck in one thinking or coding approach
 * 
 * Note: If the 2 given vectors were already sorted, we can develop a linear solution
 * 		https://leetcode.com/problems/heaters/discuss/1506995/Simple-C%2B%2B-easy-to-understand-solution
 */

class Solution {
public:
	int findRadius(vector<int> &houses, vector<int> &heaters) {
		sort(heaters.begin(), heaters.end());
		int radius = INT_MIN;

		for (int i = 0; i < (int)houses.size(); i++) {
			int idx = lower_bound(heaters.begin(), heaters.end(), houses[i]) - heaters.begin();

			if(idx == (int)heaters.size())	// after heaters
				radius = max(radius, abs(heaters[idx - 1] - houses[i]));
			else if (idx == 0)				// before heaters
				radius = max(radius, abs(heaters[idx] - houses[i]));
			else {							// surrounded by heaters: comapr idx and idx-1
				int besti_r = min(abs(heaters[idx] - houses[i]), abs(heaters[idx - 1] - houses[i]));
				radius = max(radius, besti_r);
			}
		}
		return radius;
	}
};

int main() {
	vector<int> houses {636807826,563613512,101929267,580723810,704877633,358580979,624379149,128236579};
	vector<int> heaters {530511967,110010672};

	Solution s;
	cout<<s.findRadius(houses, heaters);

	return 0;
}
