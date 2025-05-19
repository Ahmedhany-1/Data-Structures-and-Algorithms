// https://www.spoj.com/problems/PIE/

#include<iostream>
#include<vector>
#include<algorithm>
#include<climits>
#include<cmath>
#include<iomanip>
using namespace std;

double circle_area(double r) {
	const double PI = acos(-1.0);
	return PI * r * r;
}

double largest_area(vector<double> &pie_radius, int people) {
	// ToDo fill this function;
}

int main() {
	int cases, n, f;
	cin >> cases;

	while (cases--) {
		cin >> n >> f;
		vector<double> pie_radius(n);

		for (int i = 0; i < n; i++)
			cin >> pie_radius[i];

		double area = largest_area(pie_radius, f + 1);	// +1 for the host person

		cout << fixed;
		cout << setprecision(4) << area << "\n";
	}
	return 0;
}
