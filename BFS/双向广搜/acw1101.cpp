#include <iostream>
#include <cstring>
#include <queue>
#define MAXN 205
using namespace std;

int t;
int r, c;
string map[MAXN];
int dist_forward[MAXN][MAXN];
int dist_backward[MAXN][MAXN];
bool vis_forward[MAXN][MAXN];
bool vis_backward[MAXN][MAXN];
int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};
pair<int, int> start, End;
queue<pair<int, int>> q_forward;
queue<pair<int, int>> q_backward;

int bfs()
{
    while (!q_forward.empty())
        q_forward.pop();
    while (!q_backward.empty())
        q_backward.pop();

    memset(vis_forward, false, sizeof(vis_forward));
    memset(vis_backward, false, sizeof(vis_backward));
    memset(dist_forward, -1, sizeof(dist_forward));
    memset(dist_backward, -1, sizeof(dist_backward));

    q_forward.push(start);
    q_backward.push(End);
    dist_forward[start.first][start.second] = 0;
    dist_backward[End.first][End.second] = 0;
    vis_forward[start.first][start.second] = true;
    vis_backward[End.first][End.second] = true;

    while (!q_forward.empty() || !q_backward.empty())
    {
        if (!q_forward.empty())
        {
            auto t = q_forward.front();
            q_forward.pop();

            for (int i = 0; i < 4; i++)
            {
                int a = t.first + dx[i];
                int b = t.second + dy[i];

                if (a < 0 || a >= r || b < 0 || b >= c)
                    continue;
                if (map[a][b] == '#')
                    continue;

                if (!vis_forward[a][b])
                {
                    vis_forward[a][b] = true;
                    dist_forward[a][b] = dist_forward[t.first][t.second] + 1;
                    q_forward.push({a, b});
                    if (vis_backward[a][b])
                        return dist_forward[a][b] + dist_backward[a][b];
                }
            }
        }

        if (!q_backward.empty())
        {
            auto t = q_backward.front();
            q_backward.pop();

            for (int i = 0; i < 4; i++)
            {
                int a = t.first + dx[i];
                int b = t.second + dy[i];

                if (a < 0 || a >= r || b < 0 || b >= c)
                    continue;
                if (map[a][b] == '#')
                    continue;

                if (!vis_backward[a][b])
                {
                    vis_backward[a][b] = true;
                    dist_backward[a][b] = dist_backward[t.first][t.second] + 1;
                    q_backward.push({a, b});
                    if (vis_forward[a][b])
                        return dist_forward[a][b] + dist_backward[a][b];
                }
            }
        }
    }
    return -1;
}

int main()
{
    cin >> t;
    while (t--)
    {
        cin >> r >> c;
        map->clear(); // map是指针
        for (int i = 0; i < r; i++)
        {
            cin >> map[i];
            // 不需要find方法，直接遍历字符串即可
            for (int j = 0; j < c; j++)
            {
                if (map[i][j] == 'S')
                    start = {i, j};
                if (map[i][j] == 'E')
                    End = {i, j};
            }
        }
        int ret = bfs();
        if (ret == -1)
            cout << "oop!" << endl;
        else
            cout << ret << endl;
    }
    return 0;
}