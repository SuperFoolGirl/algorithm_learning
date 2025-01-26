// AI解法
#include <iostream>
#include <deque>
#include <vector>
#include <climits>
using namespace std;

struct Direction
{
    int dx, dy;
    int comp_i, comp_j;
    char expected;
};

Direction dirs[4] = {
    {1, 1, 0, 0, '\\'},     // 右下方向，对应元件(i,j)
    {-1, 1, -1, 0, '/'},    // 右上方向，对应元件(i-1,j)
    {-1, -1, -1, -1, '\\'}, // 左上方向，对应元件(i-1,j-1)
    {1, -1, 0, -1, '/'}     // 左下方向，对应元件(i,j-1)
};

int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<char>> grid(n, vector<char>(m));
    for (int i = 0; i < n; ++i)
    {
        string line;
        cin >> line;
        for (int j = 0; j < m; ++j)
        {
            grid[i][j] = line[j];
        }
    }

    const int dest_x = n, dest_y = m;
    vector<vector<int>> dist(n + 1, vector<int>(m + 1, INT_MAX));
    deque<pair<int, int>> dq;

    dist[0][0] = 0;
    dq.push_back({0, 0});

    while (!dq.empty())
    {
        auto [x, y] = dq.front();
        dq.pop_front();

        if (x == dest_x && y == dest_y)
        {
            cout << dist[x][y] << endl;
            return 0;
        }

        for (const auto &dir : dirs)
        {
            int nx = x + dir.dx;
            int ny = y + dir.dy;
            if (nx < 0 || nx > n || ny < 0 || ny > m)
            {
                continue;
            }

            int ci = x + dir.comp_i;
            int cj = y + dir.comp_j;
            if (ci < 0 || ci >= n || cj < 0 || cj >= m)
            {
                continue;
            }

            char expected = dir.expected;
            int cost = (grid[ci][cj] == expected) ? 0 : 1;
            if (dist[x][y] + cost < dist[nx][ny])
            {
                dist[nx][ny] = dist[x][y] + cost;
                if (cost == 0)
                {
                    dq.push_front({nx, ny});
                }
                else
                {
                    dq.push_back({nx, ny});
                }
            }
        }
    }

    cout << "NO SOLUTION" << endl;
    return 0;
}



// 我的解法，目前有问题，只能过几个点，待研究
#include <iostream>
#include <deque>
#include <string>
#include <cstring>
using namespace std;
#define MAXN 510

struct node
{
    int x, y;
    int rewrite;

    bool operator==(const node &a) const
    {
        return x == a.x && y == a.y && rewrite == a.rewrite;
    }
};

int n, m;
deque<node> q;
int dist[MAXN][MAXN][2]; // 参数三记录是否旋转。本题因为只有两种状态，不像魔法那个题有三种颜色，所以可以简化一些
int dx[] = {-1, -1, -1, 0, 1, 1, 1, 0};
int dy[] = {-1, 0, 1, 1, 1, 0, -1, -1};
char map[MAXN][MAXN];
node start = {0, 0, 0};
pair<int, int> End;

bool check1(char origin, int i)
{
    if (origin == '\\')
    {
        if (i == 2 || i == 6)
            return false;
    }
    else
    {
        if (i == 0 || i == 4)
            return false;
    }
    return true;
}

bool check2(char origin, char next, int i)
{
    if (origin == '\\')
    {
        if (i == 0 || i == 4)
        {
            if (next == origin)
                return true;
            else
                return false;
        }
        else
        {
            if (next != origin)
                return true;
            else
                return false;
        }
    }
    else
    {
        if (i == 2 || i == 6)
        {
            if (next == origin)
                return true;
            else
                return false;
        }
        else
        {
            if (next != origin)
                return true;
            else
                return false;
        }
    }
}

// 这个题与魔法有相似之处
// 如果走了边权为1的路，我们也记一下它现在的状态，以确定它下一步是否要花费
// 而走完了之后，默认恢复即可
int bfs()
{
    memset(dist, -1, sizeof(dist));
    q.push_back(start);
    dist[start.x][start.y][0] = 0;

    while (!q.empty())
    {
        auto t = q.front();
        q.pop_front();

        // 像魔法一样，没法判断子状态的rewrite参数，所以只能在这里判断
        if (dist[t.x][t.y][t.rewrite] != -1 && !(t == start)) // 保证起点不受影响
            continue;

        if (t.x == End.first && t.y == End.second)
            return dist[t.x][t.y][t.rewrite];

        for (int i = 0; i < 8; i++)
        {
            int a = t.x + dx[i];
            int b = t.y + dy[i];

            if (a < 0 || a >= n || b < 0 || b >= m)
                continue;

            // 有两个点是走不了的
            if (!check1(map[t.x][t.y], i))
                continue;

            // 1边权
            if (!check2(map[t.x][t.y], map[a][b], i))
            {
                dist[a][b][1] = dist[t.x][t.y][t.rewrite] + 1;
                q.push_back({a, b, 1});
            }
            // 0边权
            else
            {
                dist[a][b][0] = dist[t.x][t.y][t.rewrite];
                q.push_front({a, b, 0});
            }
        }
    }
    return -1;
}

int main()
{
    cin >> n >> m;
    End = {n - 1, m - 1}; // 输出完mn后才能赋值
    for (int i = 0; i < n; i++)
        cin >> map[i];
    int ans = bfs();
    if (ans != -1)
        cout << ans;
    else
        cout << "NO SOLUTION";
    return 0;
}