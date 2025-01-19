// 1 自己的思路 AC了
// 这里联想到了水坑，多起点搜索
// 关键在于多起点带来的更新逻辑
#include <iostream>
using namespace std;
#define maxn 510
#include <queue>
#include <cstring>

int n, m, a, b;
int dist[maxn][maxn];
int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};
queue<pair<int, int>> q;

void bfs(int x, int y)
{
    // 出bfs时队列必定时清空状态 无需清空
    // while (!q.empty())
    //     q.pop();

    q.push({x, y});

    while (!q.empty())
    {
        auto t = q.front();
        q.pop();

        for (int i = 0; i < 4; i++)
        {
            int a = t.first + dx[i];
            int b = t.second + dy[i];

            if (a < 1 || a > n || b < 1 || b > m)
                continue;
            // 注意这个逻辑的表述
            int new_dist = dist[t.first][t.second] + 1;
            if (dist[a][b] == -1 || new_dist < dist[a][b])
            {
                dist[a][b] = new_dist;
                q.push({a, b});
            }
        }
    }
}

int main()
{
    cin >> n >> m >> a >> b;
    memset(dist, -1, sizeof dist);
    for (int i = 0; i < a; i++)
    {
        int x, y;
        cin >> x >> y;
        dist[x][y] = 0;
        bfs(x, y);
    }

    for (int i = 0; i < b; i++)
    {
        int x, y;
        cin >> x >> y;
        cout << dist[x][y] << endl;
    }
    return 0;
}


// 2 AI
#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

#define maxn 510

int n, m, a, b;
int dist[maxn][maxn];
int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};
queue<pair<int, int>> q;

void bfs()
{
    while (!q.empty())
    {
        auto t = q.front();
        q.pop();

        for (int i = 0; i < 4; i++)
        {
            int a = t.first + dx[i];
            int b = t.second + dy[i];

            if (a < 1 || a > n || b < 1 || b > m)
                continue;
            if (dist[a][b] == -1)
            {
                dist[a][b] = dist[t.first][t.second] + 1;
                q.push({a, b});
            }
        }
    }
}

int main()
{
    cin >> n >> m >> a >> b;
    memset(dist, -1, sizeof dist);

    // 将所有起点加入队列
    for (int i = 0; i < a; i++)
    {
        int x, y;
        cin >> x >> y;
        dist[x][y] = 0;
        q.push({x, y});
    }

    // 进行一次 BFS 遍历
    // 多个起点同时开始搜索，齐头并进，其实更符合bfs的逻辑。
    // 其中 最先到达的点的距离是最短的，dist的值不再是-1。即使后面有再到的点，由于它肯定更大，所以不会更新dist，依旧使用!= -1的逻辑依然正确
    // 我自己写的多起点bfs反而只是模仿dfs的多起点搜索
    bfs();

    // 输出每个目标点的最短距离
    for (int i = 0; i < b; i++)
    {
        int x, y;
        cin >> x >> y;
        cout << dist[x][y] << endl;
    }

    return 0;
}