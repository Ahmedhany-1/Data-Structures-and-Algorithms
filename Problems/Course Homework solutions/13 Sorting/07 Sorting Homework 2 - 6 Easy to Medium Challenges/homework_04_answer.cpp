#include<iostream>
#include<vector>
#include<algorithm>
#include<climits>
using namespace std;

/*
 * Assume we sorted the array. Can we rearrange its elements to satisfy wiggleSort?
 * 1, 2, 3, 4, 5, 6, 7, 8
 *
 * nums[0] is the smallest in the array and satisfy the target
 *
 * The next one? All the next numbers are all valid choices
 * 	Boundary thinking? Maybe 2 (the next) or 8 (the last)
 *
 * What about the largest? This is 8
 * So now 1 8
 * The remaining numbers is what we call a sub-problem
 * 		Sub-problem: [2, 3, 4, 5, 6, 7]
 * We want them to be waggle sort
 * So we take the first (2) with the last (7)
 * and so on
 * Ending with: 1, 8, 2, 7, 3, 6, 5, 4
 *
 * We have to create O(n) memory to save the output
 * See code: wiggleSort2
 *
 * ------------------
 * Can we find another one without this O(n) memory?
 * Initially: 1, 2, 3, 4, 5, 6, 7, 8
 *
 * We again can start with 1. What is next? Maybe 2
 * This is problematic as 1 2 next: next should be < 2
 *
 * What about 3? 1 3: this is perfect as we can find 2 as min value
 * So [1, 3] then what? This is again a sub-problem
 * 		Sub-problem: [2, 4, 5, 6, 7, 8]
 * 		So take 2, then skip 4 and take 5
 * 			Sub-problem: [2, 4, 5, 6, 7, 8]
 *
 * Overall: 1 3 2 5 4 7 6 8
 * How to implement? It seems starting from index 2: just swap consecutive values!
 * see wiggleSort1
 *
 *
 *
 * This is a greedy algorithm :)
 * 		It involves smart decisions that convert the problem to a sub-problem
 *
 * ---------------------------
 * For an O(n) time solution, optionally check out attached editorial
 */

class Solution {
public:
	// O(nlogn) time and O(1) space
	void wiggleSort1(vector<int> &nums) {
		sort(nums.begin(), nums.end());

		for (int i = 1; i + 1 < (int) nums.size(); i += 2)
			swap(nums[i], nums[i + 1]);
	}

	// O(nlogn) time and O(n) space
	void wiggleSort2(vector<int> &nums) {
		sort(nums.begin(), nums.end());
		// From: 1, 2, 3, 4, 5, 6, 7, 8
		// To  : 1, 8, 2, 7, 3, 6, 5, 4

		vector<int> ans;	// O(n) extra memory

		int left = 0, right = nums.size()-1;
		while (left <= right) {
			ans.push_back(nums[left]);
			if(left != right)	// don't add same position twice   [odd case]
				ans.push_back(nums[right]);
			left += 1;
			right -= 1;
		}
		nums = ans;
	}
};

int main() {

	return 0;
}

