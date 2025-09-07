#include <bits/stdc++.h>
using namespace std;
char a[1001][1001];
bool visited[1001][1001];
vector<pair<int, int>> d = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};
int n, m;
bool isvalid(int x, int y)
{
    if (x < 0 || y < 0 || x >= n || y >= m)
        return false;
    if (a[x][y] == '#' || visited[x][y])
        return false;
    return true;
}
void dfs(int x, int y)
{
    visited[x][y] = true;
    for (auto dir : d)
    {
        int f = x + dir.first;
        int s = y + dir.second;
        if (isvalid(f, s))
        {
            dfs(f, s);
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> a[i][j];
        }
    }
    int roomcount = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (a[i][j] == '.' && !visited[i][j])
            {
                dfs(i, j);
                roomcount++;
            }
        }
    }
    cout << roomcount << endl;
}