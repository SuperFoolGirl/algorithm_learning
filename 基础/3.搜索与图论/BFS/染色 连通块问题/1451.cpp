#include <iostream>
#include <queue>
#include <string>
using namespace std;
#define maxn 110

int n, m;
queue<pair<int, int>> q;
bool vis[maxn][maxn] = {false};
string map[maxn];
int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};

void bfs(int x, int y)
{
    q.push({x, y});
    vis[x][y] = true;

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
            if (map[a][b] == '0')
                continue;
            if (vis[a][b] == true)
                continue;

            q.push({a, b});
            vis[a][b] = true;
        }
    }
}

int main()
{
    int ans = 0;
    cin >> n >> m;
    for (int i = 0; i < n; i++)
        cin >> map[i];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (map[i][j] != '0' && vis[i][j] == false)
            {
                ans++;
                bfs(i, j);
            }
        }
    }
    cout << ans;
    return 0;
}