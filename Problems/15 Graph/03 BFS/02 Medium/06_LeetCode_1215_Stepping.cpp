// https://leetcode.com/problems/stepping-numbers/

#include<iostream>
#include<vector>
#include<queue>
#include<unordered_set>
using namespace std;

/*
 This problem involves 2 styles we learned:
 - Operation-based problem
 - Multi-src BFS

 Observe: Given a positive number, we can generate maximum 2 new numbers
 34 ==> 345 or 343
 30 ==> 301
 39 ==> 398

 The idea, we can use DFS or BFS to generate ALL the numbers. Then add only the numbers in the range

 Start with the numbers from 1 to 9
 Each number generates new numbers and so on
 1 => 10 and 11
 2 => 21 and 23
 ..
 9 => 98

 and so on
 10 => 101
 11 => 110 or 112

 Observe: ALL generated numbers are unique. No need for visited array
 Observe: As we generate the numbers in order, ONCE we have a number > high
 we can safely stop as all next numbers are high
 Generated sequence: 10, 12, 21, 23, 32, 34, 43, 45, 54, 56, 65, 67, 76, 78, 87, 89, 98, 101, 121, 123, 210, 212, 232, 234, 321

 So the idea:
 - Number is a node. 2 edges are maximum
 - Start from 9 values as BFS states
 - Handle 0 as special case

 With careful thinking and verifying ==> easy code. Rush? Messy code

 */

typedef long long LL;

class Solution {
	bool inrange(LL num, LL low, LL high) {
		return low <= num && num <= high;
	}

	bool process(queue<LL> &q, vector<int> &answer, LL low, LL high, LL num) {
		if (num > high)
			return false;	// next values are just bigger

		if (inrange(num, low, high))
			answer.push_back(num);

		q.push(num);
		return true;
	}
public:
	vector<int> countSteppingNumbers(LL low, LL high) {
		// The below generation builds unique values. No need for visited
		queue<LL> q;		// large input limits
		vector<int> answer;

		if (inrange(0, low, high))	// special treatment. We can't generate from 0
			answer.push_back(0);

		for (int i = 1; i <= 9; i++) {
			q.push(i);

			if (inrange(i, low, high))
				answer.push_back(i);
		}

		for (int level = 0, sz = q.size(); !q.empty(); ++level, sz = q.size()) {
			while (sz--) {
				LL num = q.front();
				q.pop();

				int last_digit = num % 10;
				if (last_digit != 0 && !process(q, answer, low, high, num * 10 + last_digit - 1))
					break;

				if (last_digit != 9 && !process(q, answer, low, high, num * 10 + last_digit + 1))
					break;
			}
		}
		return answer;
	}
};

int main() {
	Solution s;
	s.countSteppingNumbers(0, 1000);

	return 0;
}

