#include<iostream>
#include<vector>
using namespace std;

class Solution {
private:
    // Delta for: up, right, down, left
    int dr[4]{-1, 0, 1, 0};
    int dc[4]{0, 1, 0, -1};

public:
    // Return true if this position INSIDE the 2D matrix
    bool isvalid(int r, int c, vector<vector<int>>& matrix) {
        return (r >= 0 && r < (int)matrix.size() && c >= 0 && c < (int)matrix[0].size());
    }

    void dfs(int r, int c, vector<vector<int>>& matrix, vector<vector<bool>>& visited, int oldcolor, int newcolor) {
        visited[r][c] = true, matrix[r][c] = newcolor;

        for (int d = 0; d < 4; ++d) {
            int nr = r + dr[d], nc = c + dc[d];
            if (!isvalid(nr, nc, matrix) || visited[nr][nc] || matrix[nr][nc] != oldcolor)
                continue;
            dfs(nr, nc, matrix, visited, oldcolor, newcolor);
        }
    }

    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int newColor) {
        // RxC boolean grid. Assume columns > 0
        vector<vector<bool>> visited(image.size(), vector<bool>(image[0].size()));
        dfs(sr, sc, image, visited, image[sr][sc], newColor);

        return image;
    }
};
