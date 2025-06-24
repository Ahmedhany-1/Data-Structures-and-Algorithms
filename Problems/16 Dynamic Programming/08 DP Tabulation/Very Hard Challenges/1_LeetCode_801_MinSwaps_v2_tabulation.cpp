// https://leetcode.com/problems/minimum-swaps-to-make-sequences-increasing/
#include <iostream>
#include <vector>
#include <cstring>
#include <climits>
#include <algorithm>
using namespace std;

/*

Rewriting the code as table method will require careful efforts!
This is a case where thinking from tabultion directly is an easier thinking path!

The 2 arguments will be converted directly into 2 loops

Change in definition
	memory[idx][0] = The best answer for the ith index given that no swaps are done
		swaps here for idx itself NOT idx-1 (history)
			Previously in recursion, we did these 2 choices already per idx and propagated theier effect for idx-1

		So we need to minimize that among to 2 choices: last_pair_swapped = {0 and 1}

Note as this code depends on only idx-1, we can reduce 2xN memory to O(1)

====
Writing the tabulation directly will make your logic easier
	Given idx-1, last_pair_swapped [0, 1]
		How can I generate my new state idx, last_pair_swapped [0, 1]

 */

const int OO = 1e9;

const int MAX = 100000 + 1;
int memory[MAX][2];
vector<int> A, B;

class Solution {
public:

	int minSwap(vector<int> &A, vector<int> &B) {
		// Base: No swaps for seq of length 1
		memory[0][0] = 0;
		memory[0][1] = 1;

		for (int idx = 1; idx < (int) A.size(); ++idx) {
			memory[idx][0] = OO;
			memory[idx][1] = OO;

			for (int last_pair_swapped = 0; last_pair_swapped < 2; ++last_pair_swapped) {
				int last_a = A[idx - 1], last_b = B[idx - 1];

				if (last_pair_swapped)
					swap(last_a, last_b);

				if (A[idx] > last_a && B[idx] > last_b)	
					memory[idx][0] = min(memory[idx][0], memory[idx - 1][last_pair_swapped]);


				if (A[idx] > last_b && B[idx] > last_a)
					memory[idx][1] = min(memory[idx][1], 1 + memory[idx - 1][last_pair_swapped]);
			}
		}
		return min(memory[A.size() - 1][0], memory[A.size() - 1][1]);
	}
};

int main() {
	vector<int> A { 1, 3, 5, 4 };
	vector<int> B { 1, 2, 3, 7 };
	cout << Solution().minSwap(A, B);

	return 0;
}
