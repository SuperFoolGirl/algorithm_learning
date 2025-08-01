// 又见面了 这次用双向广搜解决
// 不过存在bug
/*
双向BFS的相遇条件错误
代码允许在起点或终点相遇，但电梯移动可能形成有向图。例如：
a = 1，b = 2，elevator [1] = 0（无法移动），elevator [2] = 1（能到1）。
此时从a无法到b，但代码误认为在a相遇返回步数。
*/
// 能标0也是逆天，标了0就永远停在那一层了啊
#include <iostream>
#include <queue>
#include <cstring>
    using namespace std;
#define MAX 210

int n, a, b;
int elevator[MAX];
int dist[MAX];
queue<int> q;
int vis[MAX];

int bfs()
{
    if (a == b)
        return 0;

    memset(dist, -1, sizeof(dist));
    memset(vis, 0, sizeof(vis));
    q.push(a);
    q.push(b);
    vis[a] = 1;
    vis[b] = 2;
    dist[a] = 0;
    dist[b] = 0;

    while (!q.empty())
    {
        auto t = q.front();
        q.pop();

        for (int i : {-1, 1})
        {
            int x = t + i * elevator[t];

            if (x < 1 || x > n)
                continue;

            if (vis[x] + vis[t] == 3)
                return dist[t] + dist[x] + 1;

            if (vis[x] != 0)
                continue;

            vis[x] = vis[t];
            dist[x] = dist[t] + 1;
            q.push(x);
        }
    }
    return -1;
}

int main()
{
    cin >> n >> a >> b;
    for (int i = 1; i <= n; i++)
        cin >> elevator[i];
    cout << bfs();
    return 0;
}