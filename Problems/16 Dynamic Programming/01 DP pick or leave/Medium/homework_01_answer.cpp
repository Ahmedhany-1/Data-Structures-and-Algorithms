#include <iostream>
#include <vector>
#include <cstring>
#include <climits>
#include <cassert>
using namespace std;

/*
This is very similar to the knapsack problem
- The target is like the remaining weight
- For each item, either take or leave

- As we care about any True call, then early find if you can stop
*/

const int MAX_N = 500;
const int MAX_T = 2000 + 1;
int memory[MAX_N][MAX_T];

vector<int> v;

bool can_subset_sum(int idx, int target) {
	// Common habit: cancel first invalid states
	if (target < 0)
		return false;

	if (target == 0)
		return true;	// Critical to handle first

	if (idx == (int) v.size())
		return 0;		// can't find combination

	auto &ret = memory[idx][target];
	if (ret != -1)
		return ret;

	if (can_subset_sum(idx + 1, target))
		return ret = true;	// if leaving do it: perfect

	return ret = can_subset_sum(idx + 1, target - v[idx]);
	// we can check before subtracting but nicer way is to check
	// early in the function. Easier for complex coding
}

bool subset_sum(const vector<int> &values, int target) {
	v = values;
	memset(memory, -1, sizeof(memory));
	return can_subset_sum(0, target);
}

void process_case(const vector<int> &values, int target, bool expected) {
	bool answer = subset_sum(values, target);

	if (answer != expected) {
		cout << "Wrong results: \t";
		for (int i = 0; i < (int) values.size(); ++i)
			cout << values[i] << " ";

		cout << "\tWith target: " << target<<"\n\n";
	}
}

int main() {
	int big = 1e8;
	process_case( { 3, 12, 4, 12, 5, 2 }, 9, true);
	process_case( { 3, 40, 4, 12, 5, 2 }, 30, false);
	process_case( { 10, 20, 30, 40, 50 }, 60, true);
	process_case( { 10, 20, 30, 40, 50 }, 100, true);
	process_case( { 10, 20, 30, 40, 50 }, 90, true);
	process_case( { 10, 20, 30, 40, 50 }, 70, true);
	process_case( { 10, 20, 30, 40, 50 }, 200, false);
	process_case( { 200 }, 300, false);
	process_case( { 200 }, 200, true);
	process_case( { big, big, big, big, big }, 60, false);
	process_case( { 1, 2, 3}, 6, true);

	cout<<"Done\n";

	return 0;
}
