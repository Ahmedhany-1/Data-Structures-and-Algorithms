#include<iostream>
#include<vector>
#include<map>
#include<set>
using namespace std;

struct Edge {
	string to;
	int weight;

	bool operator < (const Edge & e) const {
		if (to != e.to)
			return to < e.to;
		return weight < e.weight;
	}
};

typedef map<string, multiset<Edge>> GRAPH;

void add_directed_edge(GRAPH &graph, string from, string to, int cost) {
	graph[from].insert({to, cost});
}

void print_adjaceny_matrix(GRAPH &graph) {

	for(auto node : graph) {
		cout << "Flights from " << node.first<<": \n";
		for(const Edge &edge : node.second)
			cout<<"\tTo "<<edge.to<<" with cost "<<edge.weight<<"\n";
	}
}

int main() {
	int nodes, edges;
	cin >> nodes >> edges;

	GRAPH graph;

	for (int e = 0; e < edges; ++e) {
		string from, to;
		int cost;
		cin >> from >> to >> cost;
		add_directed_edge(graph, from, to, cost);
	}
	print_adjaceny_matrix(graph);
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
Flights from California:
	To Florida with cost 75
	To Pennsylvania with cost 37
	To Texas with cost 10
	To Texas with cost 30
	To Texas with cost 35
Flights from Florida:
	To California with cost 70
Flights from NewYork:
	To California with cost 35
Flights from Pennsylvania:
	To Florida with cost 18
	To Florida with cost 28

 */

