// https://leetcode.com/problems/kth-smallest-number-in-multiplication-table/
#include<iostream>
#include<vector>
#include<algorithm>
#include<climits>
#include<cmath>
#include<set>
using namespace std;

/*
 * Check out public editorial
 *
 * Assume count_leq(m, n, value) returns how many numbers < value in mxn table
 * Clearly, the bigger the value, the bigger the return => monotonic
 *
 * With this function, we can trivially search for the kth number
 * 	if total numbers (mid) < k, then we don't have kth number
 *
 * How to implement count_leq?
 * We can do complete brute force in O(nm)
 *
 * Smarter brute force: brute force on m only (the rows)
 * Assume current row = 5. COLS = 7
 * This mean the row values are: 1x5  2x5  3x5  4x5   5x5  6x5  7x5
 *
 * So value 30 covers 30/5 = 6:   6 values in this row <= 30
 * So value 33 covers 33/5 = 6:   6 values in this row <= 33
 * So value 35 covers 35/5 = 7:   7 values in this row <= 40
 * So value 40 covers 40/5 = 8:   But we have 7 columns only!
 *
 * So in each row: min(value / r, cols) is the number of values <= value
 */

class Solution {
public:
	int count_leq(int rows, int cols, int value) {	// O(n)
		int count = 0;
		for (int r = 1; r <= rows; r++)
			count += min(value / r, cols);
		return count;
	}

	int findKthNumber(int m, int n, int k) {
		int start = 1, end = m * n, kth = -1;

		while (start <= end) {
			int mid = start + (end - start) / 2;
			if (count_leq(m, n, mid) < k)	// not enough
				start = mid + 1;
			else
				end = mid - 1, kth = mid;
		}
		return kth;
	}
};

int main() {

	return 0;
}
