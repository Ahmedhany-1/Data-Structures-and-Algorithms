// https://leetcode.com/problems/edit-distance
#include <iostream>
#include <vector>
#include <cstring>
#include <climits>
using namespace std;

string str1, str2;

const int MAX = 1000 + 1;
int memory[MAX][MAX];

int edit(int i, int j) {
	if (i == (int) str1.size())
		return (int) str2.size() - j;   // insert or delete remaining of s2

	if (j == (int) str2.size())
		return (int) str1.size() - i;   // insert or delete remaining of s1

	auto &ret = memory[i][j];
	if (ret != -1)
		return ret;

	// If the same letter, then logically keep it
	if (str1[i] == str2[j])
		return ret = edit(i + 1, j + 1);

	// Apply the 3 operations to generate calls
	int delete_ = 1 + edit(i + 1, j);
	int insert = 1 + edit(i, j + 1);
	int change = 1 + edit(i + 1, j + 1);
	return ret = min(min(insert, delete_), change);
}

void edit_print(int i, int j) {
	if (i == (int) str1.size() && j == (int) str2.size())
		return;	// handle e..g equal strings

	if (i == (int) str1.size()) {
		cout << "In " << str1 << " insert at the end " << str2.substr(j) << "\n";
		return;
	}

	if (j == (int) str2.size()) {
		cout << "In " << str1 << " delete the last " << (int) str1.size() - i << " letters " << str1.substr(i) << "\n";
		return;
	}

	int optimal = edit(i, j);

	if (str1[i] == str2[j]) {
		edit_print(i + 1, j + 1);
		return;
	}

	int delete_ = 1 + edit(i + 1, j);
	int insert = 1 + edit(i, j + 1);

	if (optimal == delete_) {
		cout << "In " << str1 << " delete original idx " << i << " letter " << str1[i] << "\n";
		edit_print(i + 1, j);

	} else if (optimal == insert) {
		cout << "In " << str1 << " insert at original idx " << i << " letter " << str2[j] << "\n";
		edit_print(i, j + 1);
	} else {	// change
		cout << "In " << str1 << " change letter at original idx " << i << " letter " << str1[i] << " to letter " << str2[j] << "\n";
		edit_print(i + 1, j + 1);
	}
}

// Let's hope no missing corner cases :D

class Solution {
public:
	int minDistance(string text1, string text2) {
		str1 = text1, str2 = text2;

		memset(memory, -1, sizeof(memory));

		cout << "Steps for: " << text1 << " to " << text2 << "\n";
		edit_print(0, 0);
		return edit(0, 0);
	}
};

int main() {
	Solution s1;
	cout << s1.minDistance("xy", "axy") << " steps in total\n\n";
	cout << s1.minDistance("axy", "xy") << " steps in total\n\n";
	cout << s1.minDistance("axy", "bxy") << " steps in total\n\n";
	cout << s1.minDistance("axy", "a") << " steps in total\n\n";
	cout << s1.minDistance("a", "axy") << " steps in total\n\n";
	cout << s1.minDistance("axy", "axy") << " steps in total\n\n";

	cout << s1.minDistance("horse", "ros") << " steps in total\n\n";
	cout << s1.minDistance("park", "spake") << " steps in total\n\n";
	cout << s1.minDistance("spake", "park") << " steps in total\n\n";
	cout << s1.minDistance("spakehz", "park") << " steps in total\n\n";

	return 0;
}
