// https://www.spoj.com/problems/GLASNICI/

#include<iostream>
#include<vector>
#include<algorithm>
#include<climits>
#include<cmath>
#include<iomanip>
using namespace std;

/*
 * More time, closer to deliver the msg ==> montonic
 * 	if 10 seconds deliver it, then 11 do too
 * 
 * The first person is at positions[0]. Given T time units, he can move distance T
 * The first person will start running to the right side to go to next person
 * He can end at
 * 		last_position = positions[0] + can_move_dist
 * Then the first person can broadcast the msg, which can end at
 * 		last_possible_msg_position = last_position + msg_dist
 *
 * The 2nd person needs to make sure he can even listen to the message
 * 		In the best case, he can go back T units
 * 		So his last location is: positions[i] - can_move_dist
 *
 * 		If his last position is >  last_possible_msg_position, then NO way to get the msg
 *
 * 	Assume 2nd position can get the msg. To make it possible for the 3rd person
 * 		we want to be in the last possible position
 * 		The 2nd person can't move beyond the last_possible_msg_position
 * 		And without this constraints he can go up to: positions[i] + can_move_dist
 *
 * 		The minimum between them is greedily (logically), his last possible position
 */
bool possible(vector<double> &positions, double msg_dist, double can_move_dist) {
	double last_position = positions[0] + can_move_dist;
	for (int i = 1; i < (int)positions.size(); i++) {
		double last_possible_msg_position = last_position + msg_dist;

		if (positions[i] - can_move_dist > last_possible_msg_position)
			return false;
		last_position = min(last_possible_msg_position, positions[i] + can_move_dist);
	}
	return true;
}

double min_time(vector<double> &positions, double msg_dist) {
	double start = 0.0, end = 1e9;

	while (end - start > 1e-9) {
	//for(int iter = 0; iter < 100; ++iter) {		// also works
		double mid = start + (end - start) / 2.0;
		if (possible(positions, msg_dist, mid))
			end = mid;
		else
			start = mid;
	}
	return start;
}

int main() {
	int cases, n;
	double msg_dist;
	cin >> cases;

	while (cases--) {
		cin >> msg_dist >> n;
		vector<double> positions(n);

		for (int i = 0; i < n; i++)
			cin >> positions[i];

		double time = min_time(positions, msg_dist);

		cout << fixed;
		cout << setprecision(2) << time << "\n";
	}
	return 0;
}

