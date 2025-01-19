// 1 我自己写的 用了两个dfs函数 完全仿照八皇后模型
#include <iostream>
using namespace std;
#include <cstring>
#define maxn 10

int n, k;
char map[maxn][maxn];
int row[maxn]; // 这里不能用bool
bool col[maxn];
int ans;

void dfs2(int x)
{
    if (x > k)
    {
        ans++;
        return;
    }

    // i是列 虽然我们每次dfs2锁定了k行，但这k行里的每一列都要搜索到
    for (int i = 1; i <= n; i++)
    {
        if (!col[i] && map[row[x]][i] == '#')
        {
            col[i] = true;
            dfs2(x + 1);
            col[i] = false;
        }
    }
}

void dfs1(int x, int start)
{
    if (x > k)
    {
        dfs2(1);
        return;
    }

    for (int i = start; i <= n; i++)
    {
        row[x] = i;
        dfs1(x + 1, i + 1); // 注意参数二不要写成start+1 我经常犯这个错误
    }
}

int main()
{

    while (true)
    {
        cin >> n >> k;
        if (n == -1 && k == -1)
            break;

        memset(map, 0, sizeof(map));
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
                cin >> map[i][j];
        }

        memset(row, 0, sizeof(row));
        memset(col, 0, sizeof(col));
        ans = 0;
        // 先通过dfs1找组合数，寻找参与下棋的行
        dfs1(1, 1);
        cout << ans << endl;
    }
    return 0;
}


// 2 视频解法
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
#define maxn 10

int n, k;
char map[maxn][maxn];
bool vis[maxn]; // 等价于我用的col数组
int ans = 0;

void dfs(int x, int cnt) // cnt记录当前放了几个棋子, x表示枚举到了哪一行
{
    if (cnt == k)
    {
        ans++;
        return;
    }

    if (x >= n)
        return;

    for (int i = 0; i < n; i++)
    {
        if (!vis[i] && map[x][i] == '#')
        {
            vis[i] = true;
            dfs(x + 1, cnt + 1);
            vis[i] = false;
        }
    }
    dfs(x + 1, cnt); // 这一行不放东西。这一句很关键，实现了选择组合数的功能
}

int main()
{
    while (cin >> n >> k, n > 0 && k > 0) // 学一下写法
    {
        for (int i = 0; i < n; i++)
            gets(map[i]);
        ans = 0;
        dfs(0, 0);
        cout << ans;
    }
    return 0;
}