// https://leetcode.com/problems/water-and-jug-problem/

#include<iostream>
#include<vector>
#include<queue>
#include<set>
#include<unordered_set>
#include<unordered_map>
using namespace std;




/*
 Once you think in this problem as a graph where the state is pair: current water in each juge
 Then from pair (jug1, jug2) we can try the 6 available substates (e.g. empty the first)
 Then normal BFS to find the solution
 	 Why BFS? As the search space is huge. We need to find the answer as soon as possible

 However, most of the BFS code will TLE. I don't care about that here as my goal to write this BFS states code

 Out of scope improvements:
 - This problem has O(1) math solution based on coprimes/gcd: https://leetcode.com/problems/water-and-jug-problem/discuss/83714/A-little-explanation-on-GCD-method.-C%2B%2BJavaPython
 - https://leetcode.com/problems/water-and-jug-problem/discuss/1476878/C%2B%2B-BFS-Solution

 Deciding the total number of states is out of our scope for this very irregular problem
 	 Just notice: it is not just the total number of states
 	 as we only visit a susbet

 */

class Solution {
	bool found = false;

	typedef unordered_map<int, unordered_set<int>> HASHSET;
	void process(queue<vector<int>> &q, HASHSET &visited, int jug1, int jug2, int target) {
		if (jug1 + jug2 == target) {
			found = true;
			return;
		}
		if (jug1 > jug2)  		// optimization: let's make the state canonical
			swap(jug1, jug2);

		if (!visited[jug1].count(jug2)) {
			visited[jug1].insert(jug2);
			q.push( { jug1, jug2 });
		}
	}

public:
	bool canMeasureWater(int CAP1, int CAP2, int target) {
		if (CAP1 + CAP2 == target)
			return 1;

		if (CAP1 + CAP2 < target)
			return 0;

		queue<vector<int>> q;
		HASHSET visited;
		found = false;
		process(q, visited, 0, 0, target);

		while (!found && !q.empty()) {
			int jug1 = q.front()[0], jug2 = q.front()[1];
			q.pop();

			int m1 = min(jug1, CAP2 - jug2), m2 = min(jug2, CAP1 - jug1);
			process(q, visited, 0, jug2, target);	// empty 1
			process(q, visited, jug1, 0, target);	// empty 2
			process(q, visited, CAP1, jug2, target);	// fill 1
			process(q, visited, jug1, CAP2, target);	// fill 2
			process(q, visited, jug1 - m1, jug2 + m1, target);	// pour from 1
			process(q, visited, jug1 + m2, jug2 - m2, target);	// pour from 2
		}
		return found;
	}
};

int main() {
	//freopen("02_LeetCode_365_Jug-input.txt", "rt", stdin);

	int cases;
	cin >> cases;

	while (cases--) {
		int jug1, jug2, cap;
		cin >> jug1 >> jug2 >> cap;

		Solution s;
		cout << s.canMeasureWater(jug1, jug2, cap) << "\n";
	}

	return 0;
}

/*
	Think of 2D array (jug1 x jug2) and flatten the array


	long long id(long long jug1, long long jug2) {
		return jug1 * 1000001 + jug2;	// convert to a single value (flat 2d array)
	}

	typedef unordered_set<long long> HASHSET;
	void process(queue<vector<int>> &q, HASHSET &visited, int jug1, int jug2, int target) {
		if (jug1 + jug2 == target) {
			found = true;
			return;
		}
		if (jug1 > jug2)  		// optimization: let's make the state canonical
			swap(jug1, jug2);

		if (visited.insert(id(jug1, jug2)).second)
			q.push( { jug1, jug2 });
	}

*/

/*
 Using unordered_set with hash function (TLE)

 typedef unordered_set<vector<int>, vector_hasher> HASHSET;

 class vector_hasher {
 public:
	 size_t operator()(vector<int> const &vec) const {
		 size_t ret = 0;
			for (auto &i : vec) {
			ret ^= hash<int>()(i);
		 }
		return ret;
	 }
 };



 void process(queue<vector<int>> &q, HASHSET &visited, int jug1, int jug2, int target) {
	 if (jug1 + jug2 == target) {
		found = true;
		return;
	 }
	 if(jug1 > jug2)  		// optimization: let's make the state canonical
	 swap(jug1, jug2);

	 if (visited.insert( { jug1, jug2 }).second)
		q.push( { jug1, jug2 });
 }

 */

