#include<iostream>
#include<vector>
#include<algorithm>
#include<climits>
using namespace std;

/*
 * Assume N is the number of jobs, and Q is the number of people
 *
 * How to brute force?
 * For every person:
 * 	For every job
 * 		if job's difficulty <= person's difficulty
 * 			maximize person's profit
 *
 * This is a simple O(NQ). Can we improve? the inner loop?
 *
 * Observe: workerA has difficulty 10 and workerB has difficulty 15
 * 		Then workerB includes the max profit from workerA
 * 		In other words: if we know workerA did jobs (x,y,z) with profit 70
 * 			workerB doesn't need to check (x,y,z). Just start from previous profit 70
 *
 *
 * How can we use this hint to skip duplicate operations?
 * First: Sort both the jobs and workers based on difficulty
 *
 * Assume jobs after sorting are
 * 	difficulty: 5 10 12 15 40
 * 	profit:     7 2  6  3  17
 *
 * We have sorted workers  [10, 15]
 * WorkerA: Scan as long as the job's difficulty <= his difficulty
 * 	This scans (5, 10) and takes max (7, 2) = 7
 *
 * Now workerB should scans (5, 10) and takes max (7, 2, 6, 3)
 * 	But why do this duplicates work
 * 		Just continue after workerA consider his profit
 * 			so only scan (6, 3) and their max with 7 ==> 7
 *
 * This is an example of making the processing smarter and faster by
 * 	figuring out where are the duplicate processing and HOW TO UTILIZE older computations
 *
 * Complexity: O(NlogN + QlogQ)  for the first 2 sorting operations
 * The profit calculation are just O(N+Q)
 *
 * Space Complexity:O(N) for jobs vector
 */
class Solution {
public:
	int maxProfitAssignment(vector<int> &diff, vector<int> &pro, vector<int> &worker) {
		vector<pair<int, int>> jobs;
		// Sort by difficulty
		for (int i = 0; i < (int) diff.size(); i++)
			jobs.push_back( { diff[i], pro[i] });
		sort(worker.begin(), worker.end());
		sort(jobs.begin(), jobs.end());

		int job = 0, mxProfitSofar = 0, total_profit = 0;
		for (int i = 0; i < (int) worker.size(); i++) {
			for (; job < (int)jobs.size() && worker[i] >= jobs[job].first; ++job)
				mxProfitSofar = max(mxProfitSofar, jobs[job].second);

			total_profit += mxProfitSofar;	// Best profit for the ith worker
		}
		return total_profit;
	}
};

int main() {

	return 0;
}

