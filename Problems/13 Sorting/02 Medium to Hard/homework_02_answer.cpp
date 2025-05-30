// https://leetcode.com/problems/sort-an-array/

#include<iostream>
#include<vector>
using namespace std;

// There is a simple idea
// If the smallest is -50000, we can just add 50000 to ALL the input
// This way, we shift the range to [0, 100000] instead of [-50000,50000]
// Now the code is as it is
// Shift before. Under at the end


class Solution {
public:
	vector<int> sortArray(vector<int> &array) {
		// Find the largest element of the array
        int size = array.size();
        const int SHIFT = 50000;

        for (int i = 0; i < size; ++i)
            array[i] += SHIFT;


		int max = array[0];
		for (int i = 1; i < size; ++i)
			if (array[i] > max)
				max = array[i];

		vector<int> count(max+1);	// zeros

		// Compute Frequency
		for (int i = 0; i < size; ++i)
			count[array[i]] += 1;

		int idx = 0;
		for (int i = 0; i <= max; ++i) {
			for (int j = 0; j < count[i]; ++j, ++idx)
				array[idx] = i - SHIFT;
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
