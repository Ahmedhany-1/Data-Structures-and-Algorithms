#include "bits/stdc++.h"
using namespace std;
#define ll long long
#define get_shit_done freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout); 

class Solution {
private:
    bool is_touched_boundary;

    int dx[4]{-1, 0, 1, 0};
    int dy[4]{0, 1, 0, -1};

    bool isvalid(int r, int c, vector<vector<int>>& matrix) {
        return (r >= 0 && r < (int)matrix.size() && c >= 0 && c < (int)matrix[0].size()
                && matrix[r][c] != 1);
    }

public:
    int closedIsland(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        vector<vector<int>> vis(n, vector<int>(m));

        int ans = 0;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (!vis[i][j] and grid[i][j] == 0) {
                    is_touched_boundary = false;
                    dfs(i, j, grid, vis);
                    ans += !is_touched_boundary;
                }
            }
        }
        return ans;
    }

    void dfs(int r, int c, vector<vector<int>>& grid, vector<vector<int>>& vis) {
        if (!isvalid(r, c, grid) || vis[r][c]) return;
        vis[r][c] = 1;

        if (r == 0 || r == grid.size() - 1 || c == 0 || c == grid[0].size() - 1) {
            is_touched_boundary = 1;
        }

        for (int k = 0; k < 4; k++) {
            int nx = r + dx[k], ny = c + dy[k];
            dfs(nx, ny, grid, vis);
        }

    }
};


int main() {
    // get_shit_done

}
