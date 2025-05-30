#include<iostream>
#include<vector>
using namespace std;

vector<int> countSort(const vector<int> &array) {
	// Find the largest element of the array
	int size = array.size();
	int mxVal = array[0];
	for (int i = 1; i < size; ++i)
		if (array[i] > mxVal)
			mxVal = array[i];

	// Compute Frequency
	vector<int> count(mxVal + 1);	// zeros
	for (int i = 0; i < size; ++i)
		count[array[i]] += 1;

	// Accumulate the counting
	for (int i = 1; i <= mxVal; ++i)
		count[i] += count[i - 1];

	// Find the index and put the number
	vector<int> output(size);
	for (int i = size - 1; i >= 0; --i) {
		output[count[array[i]] - 1] = array[i];
		count[array[i]] -= 1;
	}
	return output;
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
	v = countSort(v);

	for (int i = 0; i < (int) v.size(); ++i) {
		cout << v[i] << " ";
	}

	return 0;
}

