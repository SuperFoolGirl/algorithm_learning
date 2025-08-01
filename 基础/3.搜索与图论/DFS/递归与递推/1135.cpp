// 第一版 自己写的
// 逻辑没问题 但需要剪枝太多了
#include <iostream>
using namespace std;

int n, a, b;
int Min = 0x7fffffff;
int elevator[200] = {0};

void dfs(int x, int times)
{
    if (x == b)
    {
        Min = min(Min, times);
        return;
    }

    if (x + elevator[x] <= n)
        dfs(x + elevator[x], times + 1);
    if (x - elevator[x] >= 1 )
        dfs(x - elevator[x], times + 1);
}

int main()
{
    cin >> n >> a >> b;
    for (int i = 1; i <= n; i++)
        cin >> elevator[i];
    dfs(a, 0);
    if (Min == 0x7fffffff)
        cout << -1;
    else
        cout << Min;
    return 0;
}



// 第二版 AI改的
#include <iostream>
#include <algorithm>
#include <climits> // INT_MAX头文件
using namespace std;

int n, a, b;
int Min = INT_MAX;
int elevator[200] = {0};

// 没有这个会爆MLE
// 如果第二次来到同一楼层，就死循环了
bool visited[200] = {false}; // 标记楼层是否被访问过

void dfs(int x, int times)
{
    if (times >= Min) // 这个剪枝思路要掌握：如果已经超出当前保存的答案，直接舍弃
        return;

    if (x == b) // 如果到达目标楼层
    {
        Min = min(Min, times);
        return;
    }

    visited[x] = true; // 标记当前楼层为已访问

    // 尝试向上移动
    int next = x + elevator[x];
    if (next <= n && !visited[next]) // 如果移动后的楼层有效且未被访问
        dfs(next, times + 1);

    // 尝试向下移动
    next = x - elevator[x];
    if (next >= 1 && !visited[next]) // 如果移动后的楼层有效且未被访问
        dfs(next, times + 1);

    visited[x] = false; // 回溯，取消标记
}

int main()
{
    cin >> n >> a >> b;
    for (int i = 1; i <= n; i++)
        cin >> elevator[i];
    dfs(a, 0);
    if (Min == INT_MAX)
        cout << -1;
    else
        cout << Min;
    return 0;
}


// 正确解法是BFS
#include <iostream>
#include <queue>
#include <cstring>
using namespace std;
#define maxn 210

int n, a, b;
int dist[maxn];
int elevator[maxn];
int dir[] = {1, -1};
queue<int> q;

int bfs(int x)
{
    q.push(x);
    dist[x] = 0;

    while (!q.empty())
    {
        auto t = q.front();
        q.pop();

        for (int i = 0; i < 2; i++)
        {
            int next = t + dir[i] * elevator[t];

            if (next < 1 || next > n)
                continue;
            if (dist[next] != -1)
                continue;

            dist[next] = dist[t] + 1;
            if (next == b)
                return dist[next];
            else
                q.push(next);
        }
    }
    return -1; // 处理没有找到的情况
}

int main()
{
    memset(dist, -1, sizeof dist);
    cin >> n >> a >> b;
    for (int i = 1; i <= n; i++)
        cin >> elevator[i];

    if (a == b) // 特判
    {
        cout << 0;
        return 0;
    }

    cout << bfs(a);
    return 0;
}