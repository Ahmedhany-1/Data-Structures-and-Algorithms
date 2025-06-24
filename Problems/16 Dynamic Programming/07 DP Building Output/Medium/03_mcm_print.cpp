#include <iostream>
#include <vector>
#include <cstring>
#include <climits>
#include <algorithm>
#include <cassert>
using namespace std;

const int MAX = 100 + 1;
int memory[MAX][MAX];

// If the function do complex staff, we can also just save the optimal solution choice
int bracket[MAX][MAX];

vector<int> rows, cols;

int mcm(int start_idx, int end_idx) {	// O(N^3) time
	if (start_idx == end_idx)
		return 0;	// a single matrix: no multiplication

	auto &ret = memory[start_idx][end_idx];
	if (ret != -1)
		return ret;

	ret = INT_MAX;
	for (int k = start_idx; k < end_idx; k++) { // < NOT <=
		int blocks_mult = rows[start_idx] * cols[k] * cols[end_idx];
		int sub1 = mcm(start_idx, k);
		int sub2 = mcm(k + 1, end_idx);
		int total_k = blocks_mult + sub1 + sub2;

		if (ret > total_k) {
			ret = total_k;
			// Let's save the optimal choice!
			bracket[start_idx][end_idx] = k;
		}
	}

	return ret;
}

char cur_matrix;

void mcm_print(int start_idx, int end_idx) {	// O(N) time
	if (start_idx == end_idx) {
		cout << cur_matrix;
		cur_matrix += 1;
		return;
	}

	// Let's get the saved optimal solution
	int k = bracket[start_idx][end_idx];

	cout << "(";
	mcm_print(start_idx, k);
	mcm_print(k + 1, end_idx);
	cout << ")";
}

int test1(const vector<vector<int>> &data) {
	rows.resize(data.size());
	cols.resize(data.size());

	for (int i = 0; i < (int) data.size(); ++i)
		rows[i] = data[i][0], cols[i] = data[i][1];

	memset(memory, -1, sizeof(memory));
	int ans = mcm(0, (int) rows.size() - 1);	// first

	cur_matrix = 'A';
	mcm_print(0, (int) rows.size() - 1);
	cout<<"\n";
	return ans;
}

int main() {
	test1( { { 2, 3 } });
	test1( { { 2, 3 }, { 3, 4 } });
	test1( { { 1, 2 }, { 2, 3 }, { 3, 4 } });
	test1( { { 5, 10 }, { 10, 19 }, { 19, 7 }, { 7, 5 } });
	test1( { { 40, 20 }, { 20, 30 }, { 30, 10 }, { 10, 30 } });

/*
A
(AB)
((AB)C)
(((AB)C)D)
((A(BC))D)
*/

	return 0;
}

