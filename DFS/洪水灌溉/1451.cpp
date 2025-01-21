// 四联通
#include <iostream>
using namespace std;
#define maxn 110

int n, m;
string map[maxn];
bool vis[maxn][maxn] = {false};
int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};

void dfs(int x, int y)
{
    vis[x][y] = true;

    for (int i = 0; i < 4; i++)
    {
        int a = x + dx[i];
        int b = y + dy[i];

        if (a < 0 || a > n - 1 || b < 0 || b > m - 1)
            continue;
        if (map[a][b] == '0')
            continue;
        if (vis[a][b] == true)
            continue;

        // 不需要回溯，不是找路线问题
        dfs(a, b);
    }
}

int main()
{
    int ans = 0;
    cin >> n >> m;
    // 用string输入地图，起点只能是0,0
    for (int i = 0; i < n; i++)
        cin >> map[i];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (map[i][j] != '0' && vis[i][j] == false)
            {
                ans++;
                dfs(i, j);
            }
    cout << ans;
    return 0;
}