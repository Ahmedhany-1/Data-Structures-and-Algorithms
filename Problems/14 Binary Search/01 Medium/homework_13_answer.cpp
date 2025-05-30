// https://www.spoj.com/problems/GLASNICI/

#include<iostream>
#include<vector>
#include<algorithm>
#include<climits>
#include<cmath>
#include<iomanip>
using namespace std;


double min_time(vector<double> &positions, double msg_dist) {
	// TODO fill this function
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

