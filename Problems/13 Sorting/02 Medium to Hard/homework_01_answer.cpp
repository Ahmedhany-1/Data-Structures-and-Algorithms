#include<iostream>
#include<vector>
using namespace std;

// Instead of shift from position to its right, we can just swap it
// This way, we keep swapping our key untill its right position
// If the swap operation takes ~3 steps, this version is lower
// Trace the following sample: 4 7 5 1 2

void insertion_sort(vector<int> &nums) {
	for (int i = 1; i < (int) nums.size(); i++)
		for(int j = i; j-1 >= 0 && nums[j] < nums[j-1]; --j)
			swap(nums[j], nums[j-1]);
}

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
	insertion_sort(v);

	for (int i = 0; i < (int) v.size(); ++i) {
		cout << v[i] << " ";
	}

	return 0;
}

