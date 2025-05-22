#include "bits/stdc++.h"
using namespace std;
#define ll long long
#define get_shit_done freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout); 

struct edge {
    int from;
    int to;
    int cost;

    edge(int from, int to, int cost = 0) : from(from), to(to), cost(cost) {}

    bool operator < (const edge& e) const {
        return cost < e.cost;
    }

    void print() {
        cout << "There is an edge between " << from << " and " << to << " with cost: " << cost << endl;
    }

};

typedef vector<edge> GRAPH;
void add_edge(GRAPH& graph, int from, int to, int cost) {
    graph.emplace_back(from, to, cost);
}

void print_adjaceny_matrix(GRAPH& graph) {
    for (int edge = 0; edge < (int)graph.size(); ++edge)
        graph[edge].print();
}

int main() {
    get_shit_done;
    GRAPH g;
    add_edge(g, 3, 2, 5);
    add_edge(g, 0, 1, 5);
    add_edge(g, 2, 1, 4);
    add_edge(g, 4, 1, 9);
    add_edge(g, 5, 2, 6);

    sort(g.begin(), g.end());
    print_adjaceny_matrix(g);
}

/*

There is an edge between 2 and 1 with cost: 4
There is an edge between 3 and 2 with cost: 5
There is an edge between 0 and 1 with cost: 5
There is an edge between 5 and 2 with cost: 6
There is an edge between 4 and 1 with cost: 9

Time complexity is O(E)
Space Complexity is O(E)



*/