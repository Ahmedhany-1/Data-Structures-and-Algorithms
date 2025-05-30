// https://leetcode.com/problems/open-the-lock

#include<iostream>
#include<vector>
#include<queue>
#include<unordered_set>
using namespace std;

/*

Another operations-based problem. Node this time a string!
	if there is an operation that converts the string to another, then this is the edge

Hence, all what you need is to do BFS from the start string till finding the target string in this graph!
As we use strings, use hashtable unordered_set to mark visited
The deadends can be simply added to our visited set!

Tip: Carefully verify the start string/deadends

Let D = Number of digits. How many states we can have?
	4 letters each is 10 values ==> 10^4  (10^D)
	This part is what really matters

We generate the children in O(D)

So in total O(D * 10^D)
D is constant anyway

Why does this matter? To be sure number of states are reasonable

Tip: In C++, we can change the index value in O(1). 
     In langauges where the string is immutable, we construct the whole string!
*/

class Solution {
	// we can code as equation too: (c - '0' + 1) % 10 + '0'
	char next(char c) {
		if (c == '9')
			return '0';
		return c + 1;
	}
	// equation: (c - '0' - 1 + 10) % 10 + '0'
	char prev(char c) {
		if (c == '0')
			return '9';
		return c - 1;
	}
public:
	int openLock(vector<string> &deadends, string target) {
        string start = "0000";
		unordered_set<string> visited { deadends.begin(), deadends.end() };
		queue<string> q;

        if(visited.count(start))
            return -1;  // special case

        if(start == target)
            return 0;  // special case

		q.push(start);
		visited.insert(start);

		for (int level = 0, sz = 1; !q.empty(); ++level, sz = q.size()) {
			while (sz--) {
				string cur = q.front();
				q.pop();
				// build forward and backward steps
				for (int i = 0; i < 4; i++) {
					cur[i] = next(cur[i]);
					if (cur == target)
						return level + 1;

					if (visited.insert(cur).second)
						q.push(cur);

					cur[i] = prev(prev(cur[i]));	// undo then another prev
					if (cur == target)
						return level + 1;

					if (visited.insert(cur).second)
						q.push(cur);
					cur[i] = next(cur[i]);	// undo
				}
			}
		}
		return -1;
	}
};

int main() {

	return 0;
}

