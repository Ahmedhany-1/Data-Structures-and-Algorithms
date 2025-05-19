#include<iostream>
#include<vector>
#include<map>
#include<set>
using namespace std;

/*
 * Simple utility to give ids to strings: 0, 1, 2, 3, ...N-1
 * If the string has an ID, return it
 * Otherwise, give it new ID
 *
 * Using this utility
 * 	convert from string to id
 * 	convert from id to its string
 */
class ObjectIdMapper {
private:
	map<string, int> str_to_id;
	map<int, string> id_to_str;
public:
	int getId(string& str) {
		if(str_to_id.count(str))
			return str_to_id[str];

		int id = str_to_id.size();
		str_to_id[str] = id;
		id_to_str[id] = str;
		return id;
	}
	string getStr(int id) {
		return id_to_str[id];
	}
};

struct edge {
	int to;
	int cost;
};

typedef vector<vector<edge>> GRAPH;

void add_directed_edge(GRAPH &graph, int from, int to, int cost) {
	graph[from].push_back({to, cost});
}
void add_undirected_edge(GRAPH &graph, int from, int to, int cost) {
	graph[from].push_back({to, cost});
	graph[to].push_back({from, cost});
}
void print_adjaceny_matrix(GRAPH &graph, ObjectIdMapper& mapper) {
	int nodes = graph.size();
	for (int from = 0; from < nodes; ++from) {
		cout << "Node " << mapper.getStr(from) << " has neighbors: \n";
		for (int edge = 0; edge < (int) graph[from].size(); ++edge)
			cout << "\t(to "<<mapper.getStr(graph[from][edge].to)
			     << " cost "<<graph[from][edge].cost<<")\n";
	}
}

int main() {
	int nodes, edges;
	cin >> nodes >> edges;

	GRAPH graph(nodes);
	ObjectIdMapper mapper;

	for (int e = 0; e < edges; ++e) {
		string from, to;
		int cost;
		cin >> from >> to >> cost;
		int from_idx = mapper.getId(from);
		int to_idx = mapper.getId(to);
		add_directed_edge(graph, from_idx, to_idx, cost);
	}
	print_adjaceny_matrix(graph, mapper);
	return 0;
}

/*

5 9
California Texas 30
California Texas 10
Florida California 70
California Florida 75
NewYork California 35
Pennsylvania Florida 18
Pennsylvania Florida 28
California Texas 35
California Pennsylvania 37

Output
Node California has neighbors:
	(to Texas cost 30)
	(to Texas cost 10)
	(to Florida cost 75)
	(to Texas cost 35)
	(to Pennsylvania cost 37)
Node Texas has neighbors:
Node Florida has neighbors:
	(to California cost 70)
Node NewYork has neighbors:
	(to California cost 35)
Node Pennsylvania has neighbors:
	(to Florida cost 18)
	(to Florida cost 28)
 */

