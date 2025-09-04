#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 1005; // Max grid size
int n, m; // Grid dimensions
char grid[MAX_N][MAX_N]; // Grid content
bool visited[MAX_N][MAX_N]; // 2D visited array
int dist[MAX_N][MAX_N]; // Distance array
int dx[4] = {1, -1, 0, 0}; // 4-directional moves: down, up, right, left
int dy[4] = {0, 0, 1, -1};

// BFS to compute component size and distances
int bfs(int start_x, int start_y) {
    queue<pair<int, int>> q;
    q.push({start_x, start_y});
    visited[start_x][start_y] = true;
    dist[start_x][start_y] = 0;
    int component_size = 1; // Count starting cell

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        // Explore 4 directions
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx >= 0 && nx < n && ny >= 0 && ny < m && !visited[nx][ny] && grid[nx][ny] != '#') {
                visited[nx][ny] = true;
                dist[nx][ny] = dist[x][y] + 1;
                q.push({nx, ny});
                component_size++;
            }
        }
    }
    return component_size;
}

int main() {
    cin >> n >> m;
    // Read grid
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
            visited[i][j] = false;
            dist[i][j] = -1; // Initialize distances to -1 (unreachable)
        }
    }

    // Example: BFS from (0,0)
    if (grid[0][0] != '#') {
        int component_size = bfs(0, 0);
        cout << "Component size: " << component_size << endl;

        // Print distances to all reachable cells
        cout << "Distances from (0,0):\n";
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cout << dist[i][j] << " ";
            }
            cout << endl;
        }
    } else {
        cout << "Starting cell is blocked" << endl;
    }

    return 0;
}
