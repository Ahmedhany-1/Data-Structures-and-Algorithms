#include "bits/stdc++.h"
using namespace std;
#define ll long long
#define get_shit_done freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout); 

class Soluotion {
    // Delta for: up, right, down, left
	int dx[4] { -1, 0, 1, 0 };
	int dy[4] { 0, 1, 0, -1 };

    bool is_sub_island;

    bool is_valid(int i, int j, vector<vector<int>>& grid) {
        int x = (int)grid.size(), y = (int)grid[0].size();
        return (0 <= i && i < x && 0 <= j && j < y);
    }

public:
    void dfs(int i, int j, vector<vector<int>>& grid_1, vector<vector<int>>& grid_2) {
        if (!is_valid(i, j, grid_2) || grid_2[i][j] == 0) return;

        if (grid_2[i][j] != grid_1[i][j]) {
            is_sub_island = false;
            return;
        }

        grid_2[i][j] = 0; // use the same grid to mark visited

        for (int x = 0; x < 4; ++x) {
            dfs(i + dx[x], j + dy[x], grid_1, grid_2);
        }
    }

    int countSubIslands(vector<vector<int>>& grid1, vector<vector<int>>& grid2) {
        int cnt = 0, n = (int)grid2.size(), m = (int)grid2[0].size();;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid2[i][j]) {
                    is_sub_island = true;
                    dfs(i, j, grid1, grid2);
                    cnt += is_sub_island;
                }
            }

        }
        return cnt;
    }
};

int main() {
    get_shit_done
    int n, m; cin >> n >> m;
    vector<vector<int>> grid1(n, vector<int>(m)), grid2;
    grid2 = grid1;

    for(int i = 0 ; i < n ; i++){
        for(int j = 0; j < m; j++){
            cin >> grid1[i][j];
        }
    }

    for(int i = 0 ; i < n ; i++){
        for(int j = 0; j < m; j++){
            cin >> grid2[i][j];
        }
    }

    Soluotion s1;
    cout << s1.countSubIslands(grid1,grid2);
}

/*
Input:
1 1 1 0 0
0 1 1 1 1 
0 0 0 0 0 
1 0 0 0 0
1 1 0 1 1

1 1 1 0 0
0 0 1 1 1 
0 1 0 0 0 
1 0 1 1 0
0 1 0 1 0

Output:
3

*/