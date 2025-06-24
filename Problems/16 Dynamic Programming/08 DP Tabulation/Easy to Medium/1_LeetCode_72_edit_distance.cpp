// https://leetcode.com/problems/edit-distance
#include <iostream>
#include <vector>
#include <cstring>
#include <climits>
using namespace std;

string str1, str2;

const int MAX = 1000 + 3;
int memory[MAX][MAX];

class Solution {
public:

	int ans(int i, int j) {
		if (i == -1 || j == -1)
			return max(i, j) + 1;
		return memory[i][j];
	}

	int minDistance(string text1, string text2) {
		int n = text1.size(), m = text2.size();

		if(n == 0 || m == 0)	// empty strings, a special case
			return max(n, m);

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (text1[i] == text2[j])
					memory[i][j] = ans(i - 1, j - 1);
				else {
					int change = 1 + ans(i - 1, j - 1);
					int delete_ = 1 + ans(i - 1, j);
					int insert = 1 + ans(i, j - 1);
					memory[i][j] = min(min(insert, delete_), change);
				}
			}
		}
		return memory[n-1][m-1];
	}
};
int main() {
	Solution s1;
	cout << s1.minDistance("abde", "accdzg");

	return 0;
}
