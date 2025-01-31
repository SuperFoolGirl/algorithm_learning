#include <iostream>
#include <queue>
#include <string>
#include <cstring>
#define MAXN 1005
using namespace std;

int X1, X2, Y1, Y2;
int n;
int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};
// 双向广搜中 dist和vis都要用了，不过vis用于标识不同起点状态
int dist[MAXN][MAXN];
int vis[MAXN][MAXN];
string map[MAXN];
queue<pair<int, int>> q;

int bfs()
{
    // 这里需要特判 否则有误
    if (X1 == X2 && Y1 == Y2)
        return 0;

    memset(dist, -1, sizeof dist);
    memset(vis, -1, sizeof vis);

    dist[X1 - 1][Y1 - 1] = 0;
    dist[X2 - 1][Y2 - 1] = 0;
    vis[X1 - 1][Y1 - 1] = 1; // 起点扩展出来的点标为1
    vis[X2 - 1][Y2 - 1] = 2; // 终点扩展出来的点标为2
    q.push({X1 - 1, Y1 - 1});
    q.push({X2 - 1, Y2 - 1});

    while (!q.empty())
    {
        auto t = q.front();
        q.pop();

        for (int i = 0; i < 4; i++)
        {
            int a = t.first + dx[i];
            int b = t.second + dy[i];

            if (a < 0 || a >= n || b < 0 || b >= n)
                continue;
            if (map[a][b] == '1')
                continue;

            // 注意出口的位置，必须写在判断访问之前
            // 如果原点和拓展出来的点为分别为两个标记，把这两个点目前为止的路径连起来，就是双向广搜的结果
            // 这里的逻辑要求是这样的：t是队首，所以其vis值一定存在；如果(a,b)已经被对面访问过了，那这里就可以达成条件了
            if (vis[a][b] + vis[t.first][t.second] == 3)
                return dist[a][b] + dist[t.first][t.second] + 1;

            // 先判断出口，才能判断是否访问
            if (dist[a][b] != -1)
                continue;

            dist[a][b] = dist[t.first][t.second] + 1;
            if (vis[a][b] == -1)
                vis[a][b] = vis[t.first][t.second];
            q.push({a, b});
        }
    }
    return -1;
}

int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> map[i];
    cin >> X1 >> Y1 >> X2 >> Y2;
    cout << bfs() << endl;
    return 0;
}




// 双队列改写版
// 双队列虽然空间复杂度大一些，但有些复杂的题目，单队列得不出结果
#include <iostream>
#include <queue>
#include <string>
#include <cstring>
#define MAXN 1005
using namespace std;

int X1, X2, Y1, Y2;
int n;
int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};

int dist_forward[MAXN][MAXN];
int dist_backward[MAXN][MAXN];
bool visited_forward[MAXN][MAXN];
bool visited_backward[MAXN][MAXN];
string map[MAXN];
queue<pair<int, int>> q_forward;
queue<pair<int, int>> q_backward;

int bfs()
{
    if (X1 == X2 && Y1 == Y2)
        return 0;

    memset(dist_forward, -1, sizeof dist_forward);
    memset(dist_backward, -1, sizeof dist_backward);
    memset(visited_forward, false, sizeof visited_forward);
    memset(visited_backward, false, sizeof visited_backward);

    // 初始化起点
    int sx = X1 - 1, sy = Y1 - 1;
    dist_forward[sx][sy] = 0;
    visited_forward[sx][sy] = true;
    q_forward.push({sx, sy});

    // 初始化终点
    int ex = X2 - 1, ey = Y2 - 1;
    dist_backward[ex][ey] = 0;
    visited_backward[ex][ey] = true;
    q_backward.push({ex, ey});

    while (!q_forward.empty() && !q_backward.empty())
    {
        // 处理起点方向的队列
        auto t_forward = q_forward.front();
        q_forward.pop();

        for (int i = 0; i < 4; ++i)
        {
            int a = t_forward.first + dx[i];
            int b = t_forward.second + dy[i];

            if (a < 0 || a >= n || b < 0 || b >= n)
                continue;
            if (map[a][b] == '1')
                continue;

            if (!visited_forward[a][b])
            {
                dist_forward[a][b] = dist_forward[t_forward.first][t_forward.second] + 1;
                visited_forward[a][b] = true;
                q_forward.push({a, b});

                // 检查是否与终点方向相遇
                if (visited_backward[a][b])
                {
                    return dist_forward[a][b] + dist_backward[a][b];
                }
            }
        }

        // 处理终点方向的队列
        auto t_backward = q_backward.front();
        q_backward.pop();

        for (int i = 0; i < 4; ++i)
        {
            int a = t_backward.first + dx[i];
            int b = t_backward.second + dy[i];

            if (a < 0 || a >= n || b < 0 || b >= n)
                continue;
            if (map[a][b] == '1')
                continue;

            if (!visited_backward[a][b])
            {
                dist_backward[a][b] = dist_backward[t_backward.first][t_backward.second] + 1;
                visited_backward[a][b] = true;
                q_backward.push({a, b});

                // 检查是否与起点方向相遇
                if (visited_forward[a][b])
                {
                    return dist_forward[a][b] + dist_backward[a][b];
                }
            }
        }
    }

    return -1;
}

int main()
{
    cin >> n;
    for (int i = 0; i < n; ++i)
        cin >> map[i];
    cin >> X1 >> Y1 >> X2 >> Y2;
    cout << bfs() << endl;
    return 0;
}