#include <iostream>
#include <queue>
#include <cstring>
using namespace std;
#define maxn 410

int n, m;
int x, y;
// int map[maxn][maxn];
int dist[maxn][maxn];
int dx[] = {-1, -2, -2, -1, 1, 2, 2, 1};
int dy[] = {-2, -1, 1, 2, -2, -1, 1, 2};
queue<pair<int, int>> q;

void bfs(int x, int y)
{
    memset(dist, -1, sizeof dist);
    q.push({x, y});
    dist[x][y] = 0;

    while (!q.empty())
    {
        auto t = q.front();
        q.pop();
        for (int i = 0; i < 8; i++)
        {
            int a = t.first + dx[i];
            int b = t.second + dy[i];
            if (a < 1 || a > n || b < 1 || b > m)
                continue;
            if (dist[a][b] >= 0)
                continue;
            q.push({a, b});
            dist[a][b] = dist[t.first][t.second] + 1;
        }
    }
}

int main()
{
    cin >> n >> m >> x >> y;
    bfs(x, y);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
            cout << dist[i][j] << ' ';
        cout << endl;
    }
    return 0;
}