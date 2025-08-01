// 之前dfs做过
// 整体写法跟dfs一样，没办法，找连通块的模板就是这样的
// 没法按照染色问题复刻，加边也用不上
#include <iostream>
#include <queue>
#include <string>
using namespace std;
#define maxn 110

string map[maxn];
bool vis[maxn][maxn] = {false};
queue<pair<int, int>> q;
int n, m;
int dx[] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dy[] = {0, 1, 1, 1, 0, -1, -1, -1};

void bfs(int x, int y)
{
    q.push({x, y});
    vis[x][y] = true;

    while (!q.empty())
    {
        auto t = q.front();
        q.pop();

        for (int i = 0; i < 8; i++)
        {
            int a = t.first + dx[i];
            int b = t.second + dy[i];

            if (a < 0 || a > n - 1 || b < 0 || b > m - 1)
                continue;
            if (vis[a][b] == true)
                continue;
            if (map[a][b] == '.')
                continue;

            vis[a][b] = true;
            q.push({a, b});
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
            if (map[i][j] == 'W' && vis[i][j] == false)
            {
                ans++;
                bfs(i, j); // bfs里没有任何终途return，队列必定为空 不需要清理
            }
        }
    }
    cout << ans;
    return 0;
}