// https://leetcode.com/problems/sliding-puzzle/

#include<iostream>
#include<vector>
#include<queue>
#include<set>
#include<unordered_set>
#include<unordered_map>
using namespace std;

/*
This is an operation-based problem. The input is a board. A swap operation converts it to another board.
So, each board is a node and conversions build edges!

To use unordered_set directly without hash table, we can represent each grid as a string
To find the neighbors elegantly, just list them as we do in a directional 2D array, but but flatten IDs in a list

Remaining of the code is straight forward!

States? The string consists of 6 digits, 6! is total number of permutations.

O(n!) where n = 6

*/

class Solution {
private:
	string goal = "123450";

	// For each idx [0-5]: list which indices it can swap with them! Think directional array
	vector<vector<int>> dir { { 1, 3 }, { 0, 2, 4 }, { 1, 5 }, { 0, 4 }, { 3, 5, 1 }, { 4, 2 } };
public:
	int slidingPuzzle(vector<vector<int>> &board) {
		string start = "";	// convert the board to a string
		for (int i = 0; i < (int) board.size(); i++)
			for (int j = 0; j < (int) board[0].size(); j++)
				start += board[i][j] + '0';

		if (goal == start)
			return 0;

		unordered_set<string> visited;
		queue<string> q;
		q.push(start);
		visited.insert(start);

		for (int level = 0, sz = 1; !q.empty(); ++level, sz = q.size()) {
			while (sz--) {
				string cur = q.front();
				q.pop();
				int idx1 = (int) cur.find('0');

				for (int idx2 : dir[idx1]) {
					swap(cur[idx1], cur[idx2]);

					if (cur == goal)
						return level + 1;

					if (visited.insert(cur).second)
						q.push(cur);
					swap(cur[idx1], cur[idx2]);	// undo
				}
			}
		}
		return -1;
	}
};

int main() {

	return 0;
}

