// 存二维坐标可以用pair 超过两个信息点再考虑结构体
#include <iostream>
#include <queue>
#include <cstring>
using namespace std;
#define maxn 1005

queue<pair<int, int>> q;
string map[maxn];
int n;
int dist[maxn][maxn]; // 与起点的距离
int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};
int x1, y1, x2, y2;

int bfs(int x, int y)
{
    memset(dist, -1, sizeof dist); // bfs中dist数组要初始化为-1 注意sizeof用法
    q.push({x, y});                // 注意写法 需要花括号 把第一个需要拓展的点--起点加入队列
    dist[x][y] = 0;                // 起点与起点距离为0

    while (!q.empty())
    {
        auto t = q.front(); // 取出队首 注意auto用法
        q.pop();            // 取出后弹出队首
        for (int i = 0; i < 4; i++)
        {
            int a = t.first + dx[i];
            int b = t.second + dy[i];

            if (a < 0 || a > n - 1 || b < 0 || b > n - 1)
                continue;
            if (map[a][b] != '0')
                continue;
            if (dist[a][b] > 0) // 已经走过的就不再走了
                continue;

            q.push({a, b}); // 加入新的待扩展的点。注意queue是添加在队尾，因此可以实现BFS
            dist[a][b] = dist[t.first][t.second] + 1;
        }
    }
    return dist[x2 - 1][y2 - 1];
}

int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> map[i];
    cin >> x1 >> y1 >> x2 >> y2;
    cout << bfs(x1 - 1, y1 - 1) << endl;
    return 0;
}