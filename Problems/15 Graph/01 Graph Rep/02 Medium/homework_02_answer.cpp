#include "bits/stdc++.h"
using namespace std;
#define ll long long
#define get_shit_done freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout); 

struct edge {
    int to;
    int cost;

    edge(int to, int cost) : to(to), cost(cost) {}

    bool operator < (edge& e) {
        if (to == e.to)
            return cost < e.cost;
        return to < e.to;
    }
};

map<string,int> string_to_int;
map<int,string> int_to_string;
typedef vector<vector<edge>> GRAPH;

void mapping_id(string s, int &id){
    int_to_string[id] = s;
    string_to_int[s] = id;
    id++;
}

void add_directed_edge(GRAPH& graph, int from, int to, int cost) {
    graph[from].emplace_back(to,cost);   
}


void print_adjaceny_matrix(GRAPH& graph) {
    int nodes = graph.size();
	for (int from = 0; from < nodes; ++from) {
		cout << "Node " << int_to_string[from] << " has neighbors: \n";
		for (int edge = 0; edge < (int) graph[from].size(); ++edge)
			cout << "\t(to "<<int_to_string[graph[from][edge].to]
			     << " cost "<<graph[from][edge].cost<<")\n";
	}
}

int main() {
    get_shit_done
    int n, m;
    cin >> n >> m;

    GRAPH g(n);
    
    int id = 0;

    for (int i = 0, c; i < m; i++) {
        string from,to;
        cin >> from >> to >> c;
        if(!string_to_int.count(from)){
            mapping_id(from,id);
        }
        
        if(!string_to_int.count(to)){
             mapping_id(to,id);
        }
        
        add_directed_edge(g, string_to_int[from], string_to_int[to], c);
    }

    print_adjaceny_matrix(g);

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

