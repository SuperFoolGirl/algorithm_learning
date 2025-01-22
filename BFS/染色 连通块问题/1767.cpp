#include <iostream>
#include <cstring>
#include <cstdio> // gets头文件
#include <queue>
#include <cctype>
using namespace std;

char map[110][210];
bool vis[110][210] = {false};
queue<pair<int, int>> q;
int n;
int ans = 0;
int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};

void bfs(int x, int y)
{
    while (!q.empty())
        q.pop();
    q.push({x, y});
    vis[x][y] = true;
    int cnt = 0;

    while (!q.empty())
    {
        auto t = q.front();
        q.pop();

        for (int i = 0; i < 4; i++)
        {
            int a = t.first + dx[i];
            int b = t.second + dy[i];
            int len = strlen(map[a]);

            if (a < 0 || a > n - 1 || b < 0 || b > len - 1)
                continue;
            if (vis[a][b] == true)
                continue;
            if (map[a][b] != map[t.first][t.second])
                continue;

            q.push({a, b});
            vis[a][b] = true;
            cnt++;
        }
    }

    if (cnt > 0) // 不能无脑一进去就ans++，因为单人成不了家族
        ans++;
}

int main()
{
    cin >> n;
    getchar();
    for (int i = 0; i < n; i++)
        gets(map[i]); // string的话，cin没法输入前置空格；另外，string类不能做gets的参数
    for (int i = 0; i < n; i++)
        for (int j = 0; j < strlen(map[i]); j++)
            if (islower(map[i][j]) && vis[i][j] == false)
                bfs(i, j);
    cout << ans;
    return 0;
}