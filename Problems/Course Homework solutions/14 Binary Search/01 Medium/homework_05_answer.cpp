#include<iostream>
#include<vector>
#include<algorithm>
#include<climits>
#include<cmath>
#include<iomanip>
using namespace std;

/*

Assume we tried a divisor D and got sum S
Clearly, when we try D+1, the sum S decreases
Hence: sum() is a monotonic decreasing function

Then just binary search to get the smallest divisor
	possible function: sum (D) <= threshold

Log(M) time complexity
where M is the maximum value in the array

How to compute ceil? Several ways. But there is a smart way
ceil(a, b) = (a+b-1) / b
	If a%b = 0, then b-1/b = 0
	if a%b = 1+, then sum is (factor+1+b-1)/b = factor/b + 1
 */

class Solution {
public:
	int sumafterdivision(vector<int> &nums, int div) {
		int sum = 0;
		for (int i = 0; i < (int) nums.size(); i++)
			sum += (nums[i] + div - 1) / div;	// ceil equation
		return sum;
	}

	int smallestDivisor(vector<int> &nums, int threshold) {
		int start = 1, end = *max_element(nums.begin(), nums.end());
		int divisor = end;	// then all values add 1

		while (start <= end) {
			int mid = start + (end - start) / 2;
			if (sumafterdivision(nums, mid) <= threshold)
				end = mid - 1, divisor = mid;
			else
				start = mid + 1;
		}
		return divisor;
	}
};

int main() {

	return 0;
}
