#include <iostream>
#include <queue>
#include <cstring>
#define MAXN 1005
using namespace std;

int dist[MAXN][MAXN];
queue<pair<int, int>> q;
int p1, p2;
int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};

int bfs(int x, int y)
{
    // 可能涉及的预处理
    // while (!q.empty())
    //     q.pop();
    // memset(dist, -1, sizeof dist);

    q.push({x, y});
    dist[x][y] = 0;

    while (!q.empty())
    {
        auto t = q.front();
        q.pop();

        // 函数出口。出队后立刻判断，不要等到子状态一生成就判断子状态
        if (x == p1 && y == p2)
            return 0;

        for (int i = 0; i < 4; i++)
        {
            int a = x + dx[i];
            int b = y + dy[i];

            // 边界判断
            if (a < 0 || a >= p1 || b < 0 || b >= p2)
                continue;

            // 已访问判断，在非单一边权的双向队列和优先队列里，写法更复杂
            if (dist[a][b] != -1)
                continue;

            dist[a][b] = dist[x][y] + 1;
            q.push({a, b});
        }
    }
    return -1;
}