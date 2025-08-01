#include <iostream>
#include <queue>
#include <cstring>
using namespace std;
#define maxn 25

queue<pair<int, int>> q;
int x1, y1, x2, y2;
int dist[maxn][maxn];
int dx[] = {-1, -2, -2, -1, 1, 2, 2, 1, -2, -2, 2, 2};
int dy[] = {-2, -1, 1, 2, -2, -1, 1, 2, -2, 2, -2, 2};

int bfs(int x, int y)
{
    // 由于函数是强制return 第一次用完后队列不一定是干净的
    while (!q.empty())
        q.pop();

    q.push({x, y});
    dist[x][y] = 0;

    while (!q.empty())
    {
        auto t = q.front();
        q.pop();

        for (int i = 0; i < 12; i++)
        {
            int a = t.first + dx[i];
            int b = t.second + dy[i];

            if (a < 1 || a > 20 || b < 1 || b > 20)
                continue;
            if (dist[a][b] != -1)
                continue;

            dist[a][b] = dist[t.first][t.second] + 1;
            if (a == 1 && b == 1)
                return dist[a][b];
            q.push({a, b});
        }
    }
}

int main()
{
    cin >> x1 >> y1 >> x2 >> y2;
    memset(dist, -1, sizeof dist);
    cout << bfs(x1, y1) << endl;
    memset(dist, -1, sizeof dist);
    cout << bfs(x2, y2) << endl;
    return 0;
}