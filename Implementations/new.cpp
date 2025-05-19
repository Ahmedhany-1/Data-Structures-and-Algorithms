#include "bits/stdc++.h"
using namespace std;
#define ll long long
#define get_shit_done freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout); 

typedef vector<vector<int>> GRAPH;

void add_directed_edge(GRAPH &graph, int from, int to){
    graph[from][to] += 1;
}

void add_undirected_edge(GRAPH &graph, int from, int to){
    graph[from][to] += 1;
    graph[to][from] += 1;
}

int main() {
    get_shit_done
    cout << "ahmed here";
    
}