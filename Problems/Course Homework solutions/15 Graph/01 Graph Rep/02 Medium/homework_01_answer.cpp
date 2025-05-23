#include "bits/stdc++.h"
using namespace std;
#define ll long long
#define get_shit_done freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout); 

struct edge{
    string to;
    int cost;

    edge(string to, int cost): to(to),cost(cost) { }

    bool operator < (edge &e){
        if(to == e.to)
            return cost < e.cost;
        return to < e.to;
    }
};

typedef map<string, vector<edge>>GRAPH;

void add_directed_edge(GRAPH& graph, string from, string to, int cost) {
    graph[from].push_back(edge(to,cost));
}


void print_adjaceny_matrix(GRAPH &graph) {
    for(auto &[from, to] : graph){
        sort(to.begin(), to.end());
        cout << "Flightes From " << from << ": \n";
        for(auto &[city,cost] : to){
            cout << "\t\tTO " << city << " with cost: " << cost << endl;
        }

    }
}

int main() {
    get_shit_done
    int n, m; cin >> n >> m;
    GRAPH g;

    for (int i = 0,c; i < m; i++) {
        string from , to;
        cin >> from >> to >> c;
        add_directed_edge(g, from, to, c);
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
Flightes From California: 
		TO Florida with cost: 75
		TO Pennsylvania with cost: 37
		TO Texas with cost: 10
		TO Texas with cost: 30
		TO Texas with cost: 35
Flightes From Florida: 
		TO California with cost: 70
Flightes From NewYork: 
		TO California with cost: 35
Flightes From Pennsylvania: 
		TO Florida with cost: 18
		TO Florida with cost: 28


 */

