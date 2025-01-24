// 自己不会写 直接提供视频解法
// bfs与二分结合

#include <iostream>
#include <cstdlib>
using namespace std;
#include <queue>
#include <cstring>
#define maxn 510

int m, n;
queue<pair<int, int>> q;
int mark[maxn][maxn];
int altitude[maxn][maxn];
int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};
bool vis[maxn][maxn];
int total_mark = 0;
pair<int, int> start; // 只记录第一个路标起点。因为我们是不断跑图来看mid是否符合最终条件
// 我之前的想法是，跑完所有的路线，然后比出最小值来。但路线显然太多了
// 所以通过二分查找和bfs里continue的操作 对路线进行剪枝

bool check(int mid)
{
    // 别忘了多次调用bfs的话，清空队列
    while (!q.empty())
        q.pop();

    memset(vis, false, sizeof vis);
    vis[start.first][start.second] = true;
    q.push(start);
    int cnt = 1;

    while (!q.empty())
    {
        auto t = q.front();
        q.pop();

        for (int i = 0; i < 4; i++)
        {
            int a = t.first + dx[i];
            int b = t.second + dy[i];

            if (a < 1 || a > m || b < 1 || b > n)
                continue;
            // 路线剪枝。理解上来说的话，跟dfs里的剪枝很相似：当前的结果要差于已经搜索出来的最优结果，所以直接舍弃
            if (abs(altitude[a][b] - altitude[t.first][t.second]) > mid)
                continue;
            // 地图搜索一般都不能重复走
            if (vis[a][b] == true)
                continue;

            // 要认识到这个题目中bfs的作用：为二分查找提供check条件
            // 而且要注意到，这里跑图也不是乱跑，上面有abs的continue限制，我们只是会选择海拔差值小于mid的点进行扩展
            // 如果没能拓展到所有的路标，那就return false
            q.push({a, b});
            vis[a][b] = true;
            if (mark[a][b] == 1)
            {
                cnt++;
                if (cnt == total_mark)
                    return true;
            }
        }
    }
    return false;
}

int main()
{
    cin >> m >> n;

    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
            cin >> altitude[i][j];

    bool found_mark = false;
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cin >> mark[i][j];
            if (mark[i][j] == 1)
            {
                total_mark++;
                if (!found_mark)
                {
                    found_mark = true;
                    start = {i, j};
                }
            }
        }
    }

    // 二分查找，找最大值里的最小值
    int left = 0, right = 1e9 + 1;
    while (left < right)
    {
        int mid = left + right >> 1;
        if (check(mid)) // 如果满足条件，说明mid还可以更小，缩小右边界
            right = mid;
        else
            left = mid + 1;
    }
    cout << left; // 按照我学的写法，最后结果总是left
    return 0;
}