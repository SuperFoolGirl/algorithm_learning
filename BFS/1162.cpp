// 染色问题
// 第一个自己写的十分之丑陋 用的也不是多源dfs 还是水坑思路
// 有一说一 我真的很钟意水坑啊
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
#define maxn 35

int n;
int map[maxn][maxn];
vector<pair<int, int>> trace;
bool vis[maxn][maxn] = {false};
int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};
queue<pair<int, int>> q;

bool is_inner(int x, int y)
{
    if (x == 1 || x == n || y == 1 || y == n)
        return false;
    if (y == 2 || y == n - 1)
        return true;
    else
    {
        if (x == 2 || x == n - 1)
            return true;
        else
            return false;
    }
}

void bfs(int x, int y)
{
    while (!q.empty())
        q.pop();
    trace.clear();

    q.push({x, y});
    vis[x][y] = true;
    trace.push_back({x, y});

    while (!q.empty())
    {
        auto t = q.front();
        q.pop();

        for (int i = 0; i < 4; i++)
        {
            int a = t.first + dx[i];
            int b = t.second + dy[i];

            // 如果下一个是边界，且是1，那么这个联通区域就是边界联通区域
            // 注意内圈边界的表示
            // 不需要return 等待队列为空后自动退出就好
            if (is_inner(t.first, t.second) && map[a][b] == 1 && (a == 1 || a == n || b == 1 || b == n))
            {
                for (auto p : trace)
                    map[p.first][p.second] = 2;
            }

            if (a < 1 || a > n || b < 1 || b > n)
                continue;
            if (vis[a][b] == true)
                continue;
            if (map[a][b] == 1)
                continue;

            q.push({a, b});
            vis[a][b] = true;
            trace.push_back({a, b});
        }
    }
}

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
            cin >> map[i][j];
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (map[i][j] == 0)
                bfs(i, j);
        }
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
            cout << map[i][j] << ' ';
        cout << endl;
    }
    return 0;
}





// 视频讲解





// 基于第一个方法 逆向思维
// 非常好的灵机一动
// 但很遗憾 这个程序是错的 有一个我一想就觉得恶心的bug
// 方向都错了 也没什么好改的
// 但这个灵机一动有必要记录一下
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
#define maxn 35

int n;
int map[maxn][maxn];
vector<pair<int, int>> trace;
bool vis[maxn][maxn] = {false};
int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};
queue<pair<int, int>> q;

void bfs(int x, int y)
{
    while (!q.empty())
        q.pop();
    trace.clear();

    q.push({x, y});
    vis[x][y] = true;
    trace.push_back({x, y});

    while (!q.empty())
    {
        auto t = q.front();
        q.pop();

        for (int i = 0; i < 4; i++)
        {
            int a = t.first + dx[i];
            int b = t.second + dy[i];

            if (a < 1 || a > n || b < 1 || b > n)
                continue;
            if (vis[a][b] == true)
                continue;
            if (map[a][b] == 1)
                continue;

            q.push({a, b});
            vis[a][b] = true;
            trace.push_back({a, b});

            // 包围圈外部记为2
            if (a == 1 || a == n || b == 1 || b == n)
            {
                for (auto p : trace)
                    map[p.first][p.second] = 2;
            }
        }
    }
}

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
            cin >> map[i][j];
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (map[i][j] == 0)
                bfs(i, j);
        }
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            // 逆向思维
            // 包围圈外部容易表示（实际上不好表示。。毕竟我写得判断条件是错误的，只能满足一部分情况）
            // 我们把包围圈外部的都标记为2，实际上也就是能够标记内部的了
            if (map[i][j] == 0)
                map[i][j] = 2;
            if (map[i][j] == 2)
                map[i][j] = 0;
            cout << map[i][j] << ' ';
        }
        cout << endl;
    }
    return 0;
}