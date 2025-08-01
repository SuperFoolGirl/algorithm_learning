#include <iostream>
#include <queue>
#include <cstring>
using namespace std;
#define maxn 2010

int n, m;
int dist[maxn][maxn];
string map[maxn];
queue<pair<int, int>> q;
int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};

int bfs(int x, int y)
{
    q.push({x, y});
    dist[x][y] = 0;

    while (!q.empty())
    {
        auto t = q.front();
        q.pop();

        for (int i = 0; i < 4; i++)
        {
            int a = t.first + dx[i];
            int b = t.second + dy[i];

            if (a < 0 || a > n - 1 || b < 0 || b > m - 1)
                continue;
            if (dist[a][b] != -1)
                continue;
            if (map[a][b] == '#')
                continue;

            q.push({a, b});
            dist[a][b] = dist[t.first][t.second] + 1;
            if (map[a][b] == 'd')
                return dist[a][b];
        }
    }
    return -1;
}

int main()
{
    int ret;
    cin >> n >> m;
    for (int i = 0; i < n; i++)
        cin >> map[i];
    memset(dist, -1, sizeof dist);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (map[i][j] == 'm')
            {
                ret = bfs(i, j);
                break;
            }
    if (ret == -1)
        cout << "No Way!";
    else
        cout << ret;
    return 0;
}