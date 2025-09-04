#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 1005; // Max grid size
int n, m; // Grid dimensions
char grid[MAX_N][MAX_N]; // Grid content
bool visited[MAX_N][MAX_N]; // 2D visited array
int dx[4] = {1, -1, 0, 0}; // 4-directional moves: down, up, right, left
int dy[4] = {0, 0, 1, -1};

// Recursive DFS to compute component size
int dfs(int x, int y) {
    if (x < 0 || x >= n || y < 0 || y >= m || visited[x][y] || grid[x][y] == '#') {
        return 0; // Out of bounds, visited, or blocked cell
    }
    visited[x][y] = true;
    int size = 1; // Count current cell
    
    // Explore 4 directions
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        size += dfs(nx, ny);
    }
    return size;
}

int main() {
    cin >> n >> m;
    // Read grid
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
            visited[i][j] = false;
        }
    }
    
    // Example: Find size of connected component starting at (0,0)
    if (grid[0][0] != '#') {
        int component_size = dfs(0, 0);
        cout << "Component size: " << component_size << endl;
    } else {
        cout << "Starting cell is blocked" << endl;
    }
    
    return 0;
}
