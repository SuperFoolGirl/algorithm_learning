// 一眼看过去 不用bfs 果不其然超时了
#include <iostream>
#include <vector>
#include <cstdlib>
#include <climits>
#define maxn 1005
using namespace std;

int main()
{
    string map[maxn];
    int n, m;
    vector<pair<int, int>> collection_of_1;
    cin >> n >> m;
    for (int i = 0; i < n; i++)
        cin >> map[i];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            if (map[i][j] == '1')
                collection_of_1.push_back({i, j});
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (map[i][j] == '1')
                cout << 0 << ' ';
            else
            {
                int min_dist = INT_MAX;
                for (auto k : collection_of_1) // 容器的遍历
                {
                    int dist = abs(k.first - i) + abs(k.second - j);
                    min_dist = min(min_dist, dist);
                }
                cout << min_dist << ' ';
            }
        }
        cout << endl;
    }
    return 0;
}



// 多源BFS
// 多源是指从多个起点同时开始进行某种操作（如搜索、遍历等）。在算法中，多源通常用于优化某些问题，例如从多个起点同时进行广度优先搜索（BFS），以快速计算每个点到最近起点的距离。
// 多源 BFS 的实现
// 初始化：将所有起点加入队列，设置这些起点的距离为 0。
// 遍历：从队列中取出一个点，检查其相邻点。如果相邻点未被访问过，则更新其距离，并将其加入队列。
// 终止：当队列为空时，遍历结束。
#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#define maxn 1005
using namespace std;

int main()
{
    string map[maxn];
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++)
        cin >> map[i];

    // 多源 BFS 初始化
    queue<pair<int, int>> q;
    vector<vector<int>> dist(n, vector<int>(m, INT_MAX));

    // 将所有 '1' 的位置加入队列，并设置距离为 0
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (map[i][j] == '1')
            {
                dist[i][j] = 0;
                q.push({i, j});
            }
        }
    }

    // 方向数组
    int dx[] = {-1, 0, 1, 0};
    int dy[] = {0, 1, 0, -1};

    // 多源 BFS
    while (!q.empty())
    {
        auto t = q.front();
        q.pop();

        for (int i = 0; i < 4; i++)
        {
            int a = t.first + dx[i];
            int b = t.second + dy[i];

            if (a < 0 || a >= n || b < 0 || b >= m)
                continue;
            if (dist[a][b] != INT_MAX)
                continue;

            dist[a][b] = dist[t.first][t.second] + 1;
            q.push({a, b});
        }
    }

    // 输出结果
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cout << dist[i][j] << ' ';
        }
        cout << endl;
    }

    return 0;
}
