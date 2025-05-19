// https://leetcode.com/problems/parallel-courses-iii/
#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
using namespace std;

/*
 * The completion time of topological ordering is a known practical CS problem.
 * Code wise, just minor changes.
 *
 * Assume the following graph
 * 		0-1, 1-2, 3-4, 4-2  with completion times   {10, 20, 7, 15, 5}
 *
 * 	Running the classical topological sort:
 * 		ready: {0, 3}
 * 		Pop 0
 * 		ready {3, 1}
 * 		pop 3
 * 		read {1, 5}
 * 		pop 1
 * 		ready {5}
 * 		pop 5
 * 		ready {2}
 * 		pop 2
 *
 * 		Now node(2) has 2 paths before it:  10+20 and 15+5. node(2) has to wait for them.
 * 			It needs max(30, 20) = 30 BEFORE starting
 * 			then it takes 7 units, for a total 37 for node(2)
 *
 * 		The whole idea is to create vector: completionTime
 * 			Update it during the topological sort to include the full completion time
 *
 * 		We update it in an incremental way
 *
 * 		Let's simulate again:
 * 		Initially completion {0, 0, 0, 0, 0}
 * 		ready: {0, 3}
 * 		Pop 0
 * 			completion[0] = 10			# means I needed 10 time units in the best case
 * 			Now what is the effect of node(0) on its neighbor node(1)?
 * 				node(1) can't start before time(10)
 * 				completion[1] = 10      # means my paths SO FAR need 10 units to finish
 * 		ready {3, 1}
 * 		pop 3
 * 			In a similar logic	completion[3] = 15. completion[4] = 15.   (3 done - 4 not yet)
 * 		read {1, 5}
 * 		pop 1
 * 			Now node(1) is ready. completion[1] = 10 for its paths. time(1) = 20
 * 			So node(1) needs completion[1] += time(1)   ==> completion[1] = 30
 * 			What about neighbor node(2)? We just reached with completion[2] = 30
 * 		ready {5}
 * 		pop 5
 * 			In a similar logic, completion[4] += time(4)  ==> completion[4] = 20
 * 			What about neighbor node(2)?
 * 				We already know it has SO FAR completion[2] = 30  from path 0-1
 * 				But now we have new path which is completion[4] = 20
 *
 * 				However, as we have to wait, then node(2) still needs to wait 30 units
 * 					completionTime[2] = max(completionTime[2], completionTime[4]) = 30
 *
 * 		ready {2}
 * 		pop 2
 * 			completionTime[2] += time(2) ==> 30 + 7 = 37
 *
 * Looks hard? When we learn to do recursion on trees/DAGs, you will get more familiar with that style
 * 	So calm down at the moment :)
 * 
 * Take home message:
 * 	When a node wants to "aggregate" information from all sub-graphs below it (think tree paths)
 *  Then we can process and keep updating the nodes
 *
 * Note: this problem is easier think/code using recursion (dynamic programming specifically)
 * 		https://leetcode.com/problems/parallel-courses-iii/discuss/1537720/Simple-dfs-%2B-dp
 *
 */

typedef vector<vector<int>> GRAPH;

void add_directed_edge(GRAPH &graph, int from, int to) {
	graph[from].push_back(to);
}

vector<int> completionTime(const GRAPH &adjList, vector<int> &time) {
	int sz = adjList.size();
	vector<int> indegree(sz, 0);
	for (int i = 0; i < sz; ++i)
		for (int j : adjList[i])
			indegree[j]++;

	queue<int> ready;
	for (int i = 0; i < sz; ++i)
		if (!indegree[i])
			ready.push(i);

	// If a node is processed: then completionTime[i] = the min time we need to complete it
	// If not, completionTime[i] = the min possible time so far among all i'th node prerequisites
	vector<int> completionTime(adjList.size());

	while (!ready.empty()) {
		int i = ready.front();
		ready.pop();
		completionTime[i] += time[i];	// Add my time to longest path time

		for (int j : adjList[i]) {
			if (--indegree[j] == 0)
				ready.push(j);
			// Node i can reach node j with time: completionTime[i]
			// Node j has several paths to it. Which one is the maximum SO FAR?
			completionTime[j] = max(completionTime[j], completionTime[i]);
		}
	}	// assume no cycles
	return completionTime;
}

class Solution {
public:
	int minimumTime(int n, vector<vector<int>> &edges, vector<int> &time) {
		GRAPH graph(n);

		for (auto &edge : edges)
			add_directed_edge(graph, edge[0] - 1, edge[1] - 1);

		vector<int> ct = completionTime(graph, time);
		return *max_element(ct.begin(), ct.end());
	}
};

int main() {

	return 0;
}
