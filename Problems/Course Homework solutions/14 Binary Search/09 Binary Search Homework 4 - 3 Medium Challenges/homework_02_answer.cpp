// https://www.spoj.com/problems/PIE/

#include<iostream>
#include<vector>
#include<algorithm>
#include<climits>
#include<cmath>
#include<iomanip>
using namespace std;

/*
 * The bigger the pie area, the less people can eat an equally sized pie
 * 	==> monotonic decreasing
 *
 * Given a piece area size, we can see how many ones can eat for each pie
 * 	The total covered people tell us if this is good or not
 */

double circle_area(double r) {
	const double PI = acos(-1.0);
	return PI * r * r;
}

int total_can_eat(vector<double> &area, double x) {
	int can_eat = 0;
	for (int i = 0; i < (int) area.size(); i++)
		can_eat += (int) (area[i] / x);
	return can_eat;
}

double largest_area(vector<double> &pie_radius, int people) {
	double start = 0, end = 0;
	vector<double> area(pie_radius.size());

	for (int i = 0; i < (int) pie_radius.size(); i++) {
		area[i] = circle_area(pie_radius[i]);
		end = max(end, area[i]);
	}

	//while(fabs(start-end) < 1e-9)	{	// Wrong answers
	for (int i = 0; i < 100; i++) {
		double mid = (start + end) / 2;
		if (total_can_eat(area, mid) >= people)
			start = mid;
		else
			end = mid;
	}
	return start;
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
