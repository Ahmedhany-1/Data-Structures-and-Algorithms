// https://leetcode.com/problems/longest-increasing-path-in-a-matrix/

/*
 * The problem is asking for the longest path.
 * 		We learned before, the longest path is efficiently solvable in DAG
 *
 * We also, know the matrix can be represented as a graph?
 *
 * Let's analyze it 2 neighbor cells
 * values (3, 5): first is connected to 2nd
 * values (5, 3): second is connected to first
 * values (5, 5): no edge
 *
 * Clearly, the matris is a DAG!
 *
 * So all what we need to do, is to apply level-by-level topological sort the same as parallel-courses
 * 	Just on a matrix rather than a graph
 *
 */

#include<iostream>
#include<vector>
#include<queue>
using namespace std;

typedef vector<vector<int>> GRAPH;

void add_directed_edge(GRAPH &graph, int from, int to) {
	graph[from].push_back(to);
}

class Solution {
	struct node {
		int r, c;
	};

	int dr[4] { -1, 0, 1, 0 };
	int dc[4] { 0, 1, 0, -1 };

	bool isvalid(int r, int c, vector<vector<int>> &matrix) {
		if (r < 0 || r >= (int) matrix.size())
			return false;
		if (c < 0 || c >= (int) matrix[0].size())
			return false;
		return true;
	}
	// return list of my neighbors + my in-degree
	pair<vector<node>, int> neighbors(int r, int c, vector<vector<int>> &matrix) {
		vector<node> edges;
		int indegree = 0;
		for (int d = 0; d < 4; ++d) {
			int nr = r + dr[d], nc = c + dc[d];
			if (!isvalid(nr, nc, matrix))
				continue;
			if (matrix[r][c] < matrix[nr][nc])			// outgoing edge
				edges.push_back( { nr, nc });
			else if (matrix[r][c] > matrix[nr][nc])		// incoming edge
				++indegree;
			// == => No edges
		}
		return {edges, indegree};
	}
public:
	int longestIncreasingPath(vector<vector<int>> &matrix) {
		int rows = matrix.size(), cols = matrix[0].size();

		vector<vector<int>> indegree(rows, vector<int>(cols));	// rows x columns
		queue<node> ready;

		for (int r = 0; r < rows; ++r) {
			for (int c = 0; c < cols; ++c) {
				indegree[r][c] = neighbors(r, c, matrix).second;

				if (indegree[r][c] == 0)
					ready.push( { r, c });
			}
		}

		int levels = 0;
		while (!ready.empty()) {
			int level_sz = ready.size();
			while (level_sz--) {
				int r = ready.front().r, c = ready.front().c;
				ready.pop();
				vector<node> neighbors_nodes = neighbors(r, c, matrix).first;

				for (auto node : neighbors_nodes)
					if (--indegree[node.r][node.c] == 0)
						ready.push(node);
			}
			++levels;
		}
		return levels;
	}
};

int main() {

	return 0;
}

