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
// 思路还是找不能染色的，然后反向输出
// 我的灵机一动确实不错 但找不能染色的方法错了
// 我当时还开了一个痕迹数组，其实想多了
// 按照bfs模板，三句continue(边界、vis、map)可以得到一个事实：永远走不到1
// 而需要染色的区域，是在1的基础上，才能走的到的
// 所以，到不了1，就到不了染色区。就是这么简单。痕迹数组纯纯招笑
// 在这个逻辑基础上，处理一下边界条件即可
// 这里借鉴求行列式的一个伟大方法：加边法
// 把外面一圈都写成0，这样无脑传0,0首坐标
// 否则就要像我一样，先遍历所有的0，然后水坑思路
#include <iostream>
#include <queue>
using namespace std;
#define maxn 35

int n;
int map[maxn][maxn] = {0};
bool vis[maxn][maxn] = {false};
queue<pair<int, int>> q;
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

            if (a < 0 || a > n + 1 || b < 0 || b > n + 1) // 注意加边带来的边界处理，全部往外扩一层
                continue;
            if (vis[a][b] == true)
                continue;
            if (map[a][b] == 1)
                continue;

            vis[a][b] = true;
            q.push({a, b});
        }
    }
}

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            cin >> map[i][j];
    bfs(0, 0); // 加边发力了
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (map[i][j] == 0 && vis[i][j] == false)
                map[i][j] = 2;
            cout << map[i][j] << ' ';
        }
        cout << endl;
    }
    return 0;
}



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