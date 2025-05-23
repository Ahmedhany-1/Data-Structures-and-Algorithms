#include<iostream>
#include<vector>
#include<cassert>
using namespace std;

/*
 * This problem requires a good deal of thinking and serious trial to prove correctness
 *
 * Recall from quiz: In a directed graph, there is at most one universal sink:
 * 	Assume vertex 0 is universal sink. So all other nodes go to 0.
 * 	Assume vertex 1 is another universal sink. Then all other nodes also go to 1.
 * 	But node 0 doesn't, which is contradiction.
 * 	Hence, if we have a universal sink, we can't have another
 *
 * Let's go to the coding problem. The easy parts:
 *
 * is_universal_sink(i)
 * 	an easy function: we just brute force to verify the universal sink condition
 * 		node i doesn't link to any node
 * 		other n-1 nodes link to node i
 * 		O(|V|)
 *
 * 	find_universal_sink_slow
 * 		is just a brute force solution for the problem. It checks every solution
 * 		Tip: we can use brute force to verify our coding
 *
 * To develop an efficient algorithm: we need to analyze much more!
 *
 * Assume we have a graph of N nodes. Consider 2 nodes (i, j)
 * 	We have 4 cases to graph[i][j] and graph[j][i]: 00, 01, 10, 11
 * 	If both are 0 or both are 1 ==> Neither i nor j are sink
 * 	graph[i][j] = 1 ==> j MAYBE a sink. i is not a sink
 * 	graph[j][i] = 1 ==> i MAYBE a sink. j is not a sink
 *
 * The major key to develop O(|V|) solution is to avoid DUPLICATE processing
 *
 * We start with i = 0 and assume it is a sink so far
 * Compare i against j, starting from 0
 * As long as i MAYBE a sink, we move to next j
 * Assume so far we compared i = 0 vs j = {0, 1, 2, 3, 4, 5}
 * The critical observation here these 6 values in j CAN'T be sink as graph[i][j] = 0
 * Assume with the next j, we found graph[i][j] = 1
 * Now, even i is not sink. We need to try another node as sink
 * but remember ALL previous values of j are NOT sink
 * So we better start from the first j that MAYBE sink
 *
 * But there is a trap here!
 * Assume the new i remained MAYBE sink for all next values of j
 * We don't know if new i is also MAYBE sink with the old j values
 * We can't adjust the algorithm to verify that because it will be O(|V|^2)
 * There is a trivial workaround
 * After you are done, use is_universal_sink(i) to check if the last valid i is really sink or not
 *
 * This end up with the code in find_universal_sink_fast: but it could be a bit tricky to write
 *
 * I am also providing a shorter code.
 * 	We just reduced the number of checking and updates we do
 * 	But this code is a bit slower but still O(|V|)
 *
 * Overall not easy problem. It requires good analysis skills. Thinking in proof will help you figure out missing part
 *
 * Please refer to the PDF for proof for the shorter code and how to build it in a systematic way
 */


typedef vector<vector<int>> GRAPH;

void add_directed_edge(GRAPH &graph, int from, int to) {
	graph[from][to] += 1;
}

bool is_universal_sink(GRAPH &graph, int i) {	// O(V)
	for (int j = 0; j < (int) graph.size(); ++j) {
		// Node i doesn't link to any other node j, including itself (loop)
		if (graph[i][j])
			return false;
		// Every node must link to i (except myself)
		if (i != j && !graph[j][i])
			return false;
	}
	return true;
}

int find_universal_sink_slow(GRAPH &graph) {	// O(V^2)
	for (int i = 0; i < (int) graph.size(); ++i)
		if (is_universal_sink(graph, i))
			return i;
	return -1;
}

int find_universal_sink_fast(GRAPH &graph) {	// O(V)
	int i = 0, j = 0, sz = graph.size();

	while (i < sz && j < sz) {
		if (i == j) {
			if (graph[i][i]) 	// self loop
				i = j = j + 1;
			else
				j = i + 1;
			continue;
		}
		// 4 possible cases: choose valid (i, j) values
		if (!graph[i][j]) {
			if (graph[j][i])
				++j;			// i is still sink. j can't be sink. Move to next j
			else
				// Neither i nor j are sink. While we move to next node (j+1),
				// No idea a sink >= j+1 is valid relative to nodes < j
				// So we must verify later again is_universal_sink(i)
				i = j = j + 1;	// Start after current j
		} else {				// i can't be sink
			if (graph[j][i])	// j also not sink
				i = j = j + 1;	// Start after current j
			else
				i = j;			// j maybe a sink
		}
	}
	// The last valid i maybe a sink. Let's confirm that
	if (i >= sz || !is_universal_sink(graph, i))
		return -1;
	return i;
}

// Given that we anyway we will verify later
// We can simplify the conditions to just move i to i+1 to check another as sink
//
int find_universal_sink_fast_shorter(GRAPH &graph) {	// O(V)
	int i = 0, j = 0, sz = graph.size();

	while (i < sz && j < sz) {
		if(graph[i][j])
			i = i+1;
		else
			j = j+1;
	}
	if (i >= sz || !is_universal_sink(graph, i))
		return -1;
	return i;
}

int main() {
	//freopen("find_sink-input.txt", "rt", stdin);	// read from find_sink-input.txt NOT cosole

	int cases, nodes, edges;
	cin>>cases;

	while (cases--) {
		cin >> nodes >> edges;
		GRAPH graph(nodes, vector<int>(nodes));

		for (int e = 0; e < edges; ++e) {
			int from, to;
			cin >> from >> to;
			add_directed_edge(graph, from, to);
		}
		int ans = find_universal_sink_fast(graph);
		cout << ans << "\n";
		assert(ans == find_universal_sink_slow(graph));
	}

	return 0;
}

/*
8
6 5
0 3
1 3
2 3
4 3
5 3

6 9
0 3
1 3
2 3
4 3
3 5
0 5
1 5
2 5
4 5

1 0

3 0

1 1
0 0

3 3
0 0
1 1
2 2

5 4
0 1
1 2
2 3
3 4

5 8
0 1
1 2
2 3
4 3
3 2
4 3
0 1
4 3

Output
3
5
0
-1
-1
-1
-1
-1

 */

