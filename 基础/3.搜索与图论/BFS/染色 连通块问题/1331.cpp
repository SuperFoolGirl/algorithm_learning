// 写一个判断矩形的函数
// 遍历 找到左上顶点和右下顶点，得到两个坐标，能够计算出矩形的面积，与目标面积进行比较
// 左上顶点一定是横纵坐标都最小，如果不存在两个维度都最小的坐标，那么矩阵不成立，直接可以判否
// 右下顶点同理

// 实测这个思路会有bug
// 但整体思路来说问题不大，取四个坐标遍历两个for循环即可
// 通过将ship排序，可以直接取到左上右下两个坐标
// 但还是不够。有可能满足这样一种情况：遍历到的只是图形的一部分，这一部分满足，最终返回true
// 所以还要加一个面积检验

#include <iostream>
#include <queue>
#include <string>
#include <climits>
#include <algorithm>
using namespace std;
#define maxn 1010

int r, c;
queue<pair<int, int>> q;
bool vis[maxn][maxn] = {false};
vector<pair<int, int>> ship;
string map[maxn];
int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};

bool is_matrix()
{
    int min_x = ship.front().first;
    int min_y = ship.front().second;
    int max_x = ship.back().first;
    int max_y = ship.back().second;

    // 注意 这个命题不能反过来说
    // 面积不相等，一定不是矩形；但面积相等，则不一定是矩形
    if ((max_x - min_x + 1) * (max_y - min_y + 1) != ship.size())
        return false;

    for (int i = min_x; i <= max_x; i++)
        for (int j = min_y; j <= max_y; j++)
            if (find(ship.begin(), ship.end(), (pair<int, int>){i, j}) == ship.end()) // find参数三不能直接写数对，否则报错“参数列表未匹配”
                return false;

    return true;
}

void bfs(int x, int y)
{
    q.push({x, y});
    vis[x][y] = true;
    ship.push_back({x, y});

    while (!q.empty())
    {
        auto t = q.front();
        q.pop();

        for (int i = 0; i < 4; i++)
        {
            int a = t.first + dx[i];
            int b = t.second + dy[i];

            if (a < 0 || a > r - 1 || b < 0 || b > c - 1)
                continue;
            if (map[a][b] == '.')
                continue;
            if (vis[a][b] == true)
                continue;

            q.push({a, b});
            vis[a][b] = true;
            ship.push_back({a, b});
        }
    }
}

bool cmp(pair<int, int> a, pair<int, int> b)
{
    if (a.first != b.first)
        return a.first < b.first; // 按 first 升序排序
    return a.second < b.second;   // 如果 first 相同，按 second 升序排序
}

int main()
{
    int ans = 0;
    cin >> r >> c;
    for (int i = 0; i < r; i++)
        cin >> map[i];
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            if (map[i][j] == '#' && vis[i][j] == false)
            {
                ship.clear();
                bfs(i, j);
                sort(ship.begin(), ship.end(), cmp); // 为后续find遍历容器提供便利
                if (!is_matrix())
                {
                    cout << "Bad placement.";
                    return 0;
                }
                ans++;
            }
        }
    }
    cout << "There are " << ans << " ships.";
    return 0;
}