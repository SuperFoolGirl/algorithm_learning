#include <iostream>
#include <queue>
#include <cstring>
using namespace std;
#define maxn 35

int m, n, m1, m2;
int dist[maxn][maxn];
int pool[maxn][maxn];
queue<pair<int, int>> q;

int bfs(int x, int y, int *dx, int *dy)
{
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

            if (a < 1 || a > m || b < 1 || b > n)
                continue;
            if (dist[a][b] != -1)
                continue;
            if (pool[a][b] != 1 && pool[a][b] != 4)
                continue;

            dist[a][b] = dist[t.first][t.second] + 1;
            if (pool[a][b] == 1)
                q.push({a, b});
            else
                return dist[a][b]; // 可以直接退出
        }
    }
}

int main()
{
    cin >> m >> n >> m1 >> m2;
    int dx[] = {-m1, -m2, -m2, -m1, m1, m2, m2, m1};
    int dy[] = {-m2, -m1, m1, m2, -m2, -m1, m1, m2};
    int startX, startY;
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cin >> pool[i][j];
            if (pool[i][j] == 3)
            {
                startX = i;
                startY = j;
            }
        }
    }
    memset(dist, -1, sizeof dist);
    cout << bfs(startX, startY, dx, dy);
    return 0;
}