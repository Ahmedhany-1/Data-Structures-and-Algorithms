#include<iostream>
#include<vector>
#include<climits>
using namespace std;

// This algorithm has the same spirit as the count sort
// For each letter, we keep list of strings started with this letter
	// Previously we used counter. Now we can't just count. We need the strings
// After building, we just print them
	// iterate on letters.
		// for non-empty lists, print them
		
// As we add the strings to the vector based on input order, output must be stable

void countSort(vector<string> &array) {
	int size = array.size();
	const int LETTERS_SZ = 26;
	vector<vector<string>> letter_to_strings(LETTERS_SZ);

	for (int i = 0; i < size; ++i)
		letter_to_strings[array[i][0] - 'a'].push_back(array[i]);

	int idx = 0;
	for (int letter = 0; letter < LETTERS_SZ; ++letter) {
		for (int str_idx = 0; str_idx < (int) letter_to_strings[letter].size(); ++str_idx, ++idx)
			array[idx] = letter_to_strings[letter][str_idx];
	}
}

vector<string> read_vector() {
	int n;
	cin >> n;

	vector<string> v(n);
	for (int i = 0; i < n; ++i)
		cin >> v[i];

	return v;
}

int main() {
	vector<string> v = read_vector();

	countSort(v);

	for (int i = 0; i < (int) v.size(); ++i)
		cout << v[i] << "\n";

	return 0;
}
