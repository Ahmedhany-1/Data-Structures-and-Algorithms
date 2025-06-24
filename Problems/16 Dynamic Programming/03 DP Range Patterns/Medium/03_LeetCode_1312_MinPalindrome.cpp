// https://leetcode.com/problems/minimum-insertion-steps-to-make-a-string-palindrome/
#include <iostream>
#include <vector>
#include <cstring>
#include <climits>
using namespace std;

/*
Very similar to lcs/edit distance style

It is a general range problem (left, right)

Case 1:  axyzwa
	as it starts/ends with the same letter
	the most logical answer is to match them
	so zero cost and new sub-problem xyzw

Case 2: xyzw
	To make this palindrom we either
		insert x in the end to match first x ==> xyzwx, so new problem is yzw
		insert w in the first to match first w ==> wxyzw, so new problem is xyz

 */

const int MAX = 500 + 1;
int memory[MAX][MAX];
string text;

int minPalindrome(int i, int j) {
	if (i >= j)
		return 0;

	auto &ret = memory[i][j];
	if (ret != -1)
		return ret;

	// If the same letter, then logically keep it
	if (text[i] == text[j])
		return ret = minPalindrome(i + 1, j - 1);

	int insert_left  = 1 + minPalindrome(i + 1, j);
	int insert_right = 1 + minPalindrome(i, j - 1);
	return ret = min(insert_left, insert_right);
}

class Solution {
public:
    int minInsertions(string s) {
        text = s;

		memset(memory, -1, sizeof(memory));
		return minPalindrome(0, (int)text.size()-1);
    }
};

int main() {

	return 0;
}
