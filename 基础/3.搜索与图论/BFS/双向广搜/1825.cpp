// 59分 有bug啊啊啊啊
#include <iostream>
using namespace std;
#include <queue>
#include <cstring>
#define MAXN 305
#include <unordered_map>

struct PairHash
{
    size_t operator()(const pair<int, int> &p) const
    {
        // hash模板函数是标准库里的
        // 类似于 int() 创建一个默认整数，hash<type>() 创建一个默认哈希函数对象
        // 第二个括号 (p.first)：调用哈希函数对象的 operator() 方法，传入 p.first 作为参数
        // 总结，第一个括号实例化对象，第二个括号是仿函数(函数对象)
        return hash<int>()(p.first) * 31 + hash<int>()(p.second);
    }
};

char map[MAXN][MAXN];
pair<int, int> start, End;
int n, m;
int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};
int dist[MAXN][MAXN];
int vis[MAXN][MAXN];
// 讲一下类模板
// unordered_map是一个类模板，它的第一个参数是键的类型，第二个参数是值的类型，第三个参数为哈希函数类型
// 类模板参数类型一律为class类型。
// 因此传入自定义哈希函数时，需要定义一个结构体，重载()运算符，然后传入这个结构体的类型。而不能直接传入函数，类模板无法接受函数参数。
// 而哈希表调用自定义类里的仿函数时，这个过程是隐式的，不需要手动调用
unordered_map<pair<int, int>, pair<int, int>, PairHash> m_tp;
unordered_map<char, pair<int, int>> m_tmp;
queue<pair<int, int>> q;

int bfs()
{
    memset(dist, -1, sizeof dist);
    memset(vis, 0, sizeof vis);
    q.push(start);
    q.push(End);
    dist[start.first][start.second] = 0;
    dist[End.first][End.second] = 0;
    vis[start.first][start.second] = 1;
    vis[End.first][End.second] = 2;

    while (!q.empty())
    {
        auto t = q.front();
        q.pop();

        // 不要检查子状态是否为传送门，在队首处检查
        if (map[t.first][t.second] >= 'A' && map[t.first][t.second] <= 'Z')
        {
            // 如果是传送门，就把它映射到另一个传送门。这个点不能再扩展了，传送门是强制走
            auto tmp = t;
            t = m_tp[t]; // 这一句很精妙

            // 新的传送门状态判断
            // 传送门没法走常规出口。如果恰好再传送门处双向搜索结束，需要特判
            if (vis[t.first][t.second] + vis[tmp.first][tmp.second] == 3)
                return dist[t.first][t.second] + dist[tmp.first][tmp.second]; // 这里没有+1，因为传送门之间没有空隙

            vis[t.first][t.second] = vis[tmp.first][tmp.second];
            dist[t.first][t.second] = dist[tmp.first][tmp.second]; // 传送门之间没有空隙，所以不需要+1
            // 到达传送门的另一端后，就可以正常扩展了
        }

        for (int i = 0; i < 4; i++)
        {
            int a = t.first + dx[i];
            int b = t.second + dy[i];

            if (a < 1 || a > n || b < 1 || b > m)
                continue;
            if (map[a][b] == '#')
                continue;

            // 出口
            if (vis[a][b] + vis[t.first][t.second] == 3)
                return dist[a][b] + dist[t.first][t.second] + 1;

            if (vis[a][b] != 0)
                continue;

            vis[a][b] = vis[t.first][t.second];
            dist[a][b] = dist[t.first][t.second] + 1;
            q.push({a, b});
        }
    }
    return -1;
}

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            cin >> map[i][j];
            if (map[i][j] == '@')
                start = {i, j};
            if (map[i][j] == '=')
                End = {i, j};
            if (map[i][j] >= 'A' && map[i][j] <= 'Z')
            {
                // 第一次遇到传送门，记一下门的种类和坐标
                if (!m_tmp.count(map[i][j])) // 注意哈希表的count可以直接判断是否访问
                    m_tmp[map[i][j]] = {i, j};
                // 第二次遇到传送门，记录两个传送门的坐标，使其互相映射
                else
                {
                    m_tp[m_tmp[map[i][j]]] = {i, j}; // vis[map[i][j]]存了第一次遇到的坐标，这里的{i,j}是二次的坐标
                    m_tp[{i, j}] = m_tmp[map[i][j]];
                }
            }
        }
    }
    cout << bfs() << endl;
    return 0;
}




// 改成双队列依然存在问题 还是59分
#include <iostream>
using namespace std;
#include <queue>
#include <cstring>
#define MAXN 305
#include <unordered_map>

struct PairHash
{
    size_t operator()(const pair<int, int> &p) const
    {
        return hash<int>()(p.first) * 31 + hash<int>()(p.second);
    }
};

char map[MAXN][MAXN];
pair<int, int> start, End;
int n, m;
int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};
int dist_forward[MAXN][MAXN];
int dist_backward[MAXN][MAXN];
bool vis_forward[MAXN][MAXN];
bool vis_backward[MAXN][MAXN];
unordered_map<pair<int, int>, pair<int, int>, PairHash> m_tp;
unordered_map<char, pair<int, int>> m_tmp;
queue<pair<int, int>> q_forward;
queue<pair<int, int>> q_backward;

int bfs()
{
    memset(dist_forward, -1, sizeof dist_forward);
    memset(dist_backward, -1, sizeof dist_backward);
    memset(vis_forward, false, sizeof vis_forward);
    memset(vis_backward, false, sizeof vis_backward);

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

            // 不要检查子状态是否为传送门，在队首处检查
            if (map[t.first][t.second] >= 'A' && map[t.first][t.second] <= 'Z')
            {
                // 如果是传送门，就把它映射到另一个传送门。这个点不能再扩展了，传送门是强制走
                auto tmp = t;
                t = m_tp[t]; // 这一句很精妙

                // 新的传送门状态判断
                // 传送门没法走常规出口。如果恰好在传送门处双向搜索结束，需要特判
                if (vis_backward[t.first][t.second])
                    return dist_backward[t.first][t.second] + dist_forward[tmp.first][tmp.second];

                vis_forward[t.first][t.second] = true;
                dist_forward[t.first][t.second] = dist_forward[tmp.first][tmp.second]; // 传送门之间没有空隙，所以不需要+1
                // 到达传送门的另一端后，就可以正常扩展了
            }

            for (int i = 0; i < 4; i++)
            {
                int a = t.first + dx[i];
                int b = t.second + dy[i];

                if (a < 1 || a > n || b < 1 || b > m)
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

            if (map[t.first][t.second] >= 'A' && map[t.first][t.second] <= 'Z')
            {
                auto tmp = t;
                t = m_tp[t];

                if (vis_forward[t.first][t.second])
                    return dist_backward[tmp.first][tmp.second] + dist_forward[t.first][t.second];

                vis_backward[t.first][t.second] = true;
                dist_backward[t.first][t.second] = dist_backward[tmp.first][tmp.second];
            }

            for (int i = 0; i < 4; i++)
            {
                int a = t.first + dx[i];
                int b = t.second + dy[i];

                if (a < 1 || a > n || b < 1 || b > m)
                    continue;
                if (map[a][b] == '#')
                    continue;

                if (!vis_backward[a][b])
                {
                    vis_backward[a][b] = true;
                    dist_backward[a][b] = dist_backward[t.first][t.second] + 1;
                    q_backward.push({a, b});

                    if (vis_forward[a][b])
                        return dist_backward[a][b] + dist_forward[a][b];
                }
            }
        }
    }
    return -1;
}

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            cin >> map[i][j];
            if (map[i][j] == '@')
                start = {i, j};
            if (map[i][j] == '=')
                End = {i, j};
            if (map[i][j] >= 'A' && map[i][j] <= 'Z')
            {
                // 第一次遇到传送门，记一下门的种类和坐标
                if (!m_tmp.count(map[i][j])) // 注意哈希表的count可以直接判断是否访问
                    m_tmp[map[i][j]] = {i, j};
                // 第二次遇到传送门，记录两个传送门的坐标，使其互相映射
                else
                {
                    m_tp[m_tmp[map[i][j]]] = {i, j}; // vis[map[i][j]]存了第一次遇到的坐标，这里的{i,j}是二次的坐标
                    m_tp[{i, j}] = m_tmp[map[i][j]];
                }
            }
        }
    }
    cout << bfs() << endl;
    return 0;
}