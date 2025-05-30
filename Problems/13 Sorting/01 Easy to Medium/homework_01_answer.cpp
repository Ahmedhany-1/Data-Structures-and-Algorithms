#include<iostream>
#include<vector>
#include<algorithm>
#include<climits>
using namespace std;

/*
 * Logically (Greedily), which monster to kill first?
 * The one that arrives the city first!
 *
 * So let's compute the time each monster needs to arrive: dist[i] / speed[i]
 * Sort them based on this arrival time
 * In each minute, kill one untill one of them arrives!
 *
 * Implementation notes:
 *
 * In eliminateMaximum2  we show the simplest code
 * Just compute time (which is double) add to vector and sort
 * Passed. But this is a bad idea, as programming languages fail to arrange close real-numbers
 *
 * In eliminateMaximum3: we handle this in a better way
 * We don't care if the monster arrives at 2.8 seconds. This just means arrive at 3 seconds.
 * So always use integers
 *
 * Third solution: for educational purposes (and challenging you): doesn't have the division/modulus operation at all
 * 		which is btw a very slow operation
 *
 * O(nlogn) time and O(n) memroy
 */

class Solution {
public:

	int eliminateMaximum3(vector<int> &dist, vector<int> &speed) {
		int sz = dist.size(), killed = 0;
		vector<int> arrival_time(sz);

		for (int i = 0; i < sz; i++) {
			if (dist[i] % speed[i] == 0)
				arrival_time[i] = dist[i] / speed[i];
			else
				arrival_time[i] = dist[i] / speed[i] + 1;
		}

		sort(arrival_time.begin(), arrival_time.end());
		for (int i = 0; i < sz && i < arrival_time[i]; i++)
			killed+=1;
		return killed;
	}

	int eliminateMaximum2(vector<int> &dist, vector<int> &speed) {
		int sz = dist.size(), killed = 0;
		vector<double> arrival_time(sz);

		for (int i = 0; i < sz; i++)
				arrival_time[i] = (double)dist[i] / speed[i];

		sort(arrival_time.begin(), arrival_time.end());
		for (int i = 0; i < sz && i < arrival_time[i]; i++)
			killed+=1;
		return killed;
	}

	static bool cmp_arrival_time(const pair<int, int>& a, const pair<int, int>& b) {
		// a/b < c/d. Multiply all sides with bd ==> ad < bc
		//return a.first / double(a.second) < b.first / double(b.second);
		return a.first * b.second < a.second * b.first;
	}

	int eliminateMaximum(vector<int>& dist, vector<int>& speed) {
		int sz = dist.size(), killed = 0;
	    vector<pair<int, int>> arrival_time;
	    for(int i = 0; i < sz; i++)
	    	arrival_time.push_back({ dist[i], speed[i] });

	    sort(arrival_time.begin(), arrival_time.end(), cmp_arrival_time);

	    for(int t = 0; t < sz; ++t) {
	        if(arrival_time[t].second * t >= arrival_time[t].first)
	        	break;	// speed*t (covered distance) >= how far: we can;t
	        killed++;
	    }
	    return killed;
	}
};

int main() {

	return 0;
}

