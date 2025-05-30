// https://leetcode.com/problems/heaters/

#include<iostream>
#include<vector>
#include<algorithm>
#include<climits>
#include<cmath>
#include<iomanip>
using namespace std;

/*
 * If radius R covers houses, then R+1 do so ==> montonic function
 * 
 * Binary search on R and check if can cover or not
 * 	Simple: iterate on heaters
 * 		cover homes as you can with this hearter
 */

class Solution {
public:
	bool possible(vector<int> &houses, vector<int> heaters, int ridus) {
		int j = 0;
		for (int i = 0; i < (int) heaters.size(); ++i) {
			// Covered range [left, right] by the ith heater
			int leftC = heaters[i] - ridus, rightC = heaters[i] + ridus;

			while (j < (int) houses.size() && leftC <= houses[j] && houses[j] <= rightC)
				++j;	// cover more houses with ith heater
		}
		return j == (int) houses.size();	// all is covered?
	}
	int findRadius(vector<int> &houses, vector<int> &heaters) {	// O(nlogn + nlogM) where M = 1e9 (or max value in arrays)
		sort(houses.begin(), houses.end());
		sort(heaters.begin(), heaters.end());

		int start = 0, end = 1e9, radius = -1;
		while (start <= end) {
			int mid = start + (end - start) / 2;
			if (possible(houses, heaters, mid))	// find smallest
				end = mid - 1, radius = mid;
			else
				start = mid + 1;
		}
		return radius;
	}
};

int main() {

	return 0;
}
