#include <iostream>
#include <queue>
#include <map>
#define maxn 260
using namespace std;

int n, m;
int ocean[maxn][maxn];
bool vis[maxn][maxn] = {false};
map<int, int> sum;
int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};
queue<pair<int, int>> q;

int bfs(int x, int y)
{
    q.push({x, y});
    vis[x][y] = true;
    int cnt = 1;

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
            if (vis[a][b] == true)
                continue;
            if (ocean[a][b] == 0)
                continue;

            q.push({a, b});
            vis[a][b] = true;
            cnt++;
        }
    }
    return cnt;
}

int main()
{
    int ans = 0;
    cin >> n >> m;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> ocean[i][j];
    int zero1, zero2;
    cin >> zero1 >> zero2;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
        {
            if (ocean[i][j] == 1 && vis[i][j] == false)
            {
                ans++;
                int ret = bfs(i, j);
                sum[ret]++; // 键 ret 不存在，插入 {ret, 0}，然后递增为 {ret, 1}
            }
        }
    cout << ans << endl;
    for (auto p : sum) // 注意map存的实际是有序键值对，只是也可以以下标形式访问
        cout << p.first << ' ' << p.second << endl;
    return 0;
}