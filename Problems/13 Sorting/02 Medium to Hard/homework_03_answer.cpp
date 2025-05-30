// https://leetcode.com/problems/sort-an-array/submissions/

#include<iostream>
#include<vector>
#include<climits>
using namespace std;

// The idea again is to make the minimum value in the array is 0
// Assume we have array with values 10 20 30
// Now minimum is 10. Subtract it from all values
// 0 10 20
// Now apply the algorithm exactly as it is
// Shift back the values 

class Solution {
public:
	vector<int> sortArray(vector<int> &array) {
		int size = array.size();
		int mxVal = array[0], mnVal = array[0];

		for (int i = 1; i < size; ++i) {
			if (array[i] > mxVal)
				mxVal = array[i];
			if (array[i] < mnVal)
				mnVal = array[i];
		}
        int new_max = mxVal - mnVal;
		vector<int> count(new_max+1);

		for (int i = 0; i < size; ++i)
			count[array[i] - mnVal] += 1;

		int idx = 0;
		for (int i = 0; i <= new_max; ++i) {
			for (int j = 0; j < count[i]; ++j, ++idx)
				array[idx] = i + mnVal;
		}
		return array;
	}
};

vector<int> read_vector() {
	int n;
	cin >> n;

	vector<int> v(n);
	for (int i = 0; i < n; ++i)
		cin >> v[i];

	return v;
}

int main() {
	vector<int> v = read_vector();

	return 0;
}
