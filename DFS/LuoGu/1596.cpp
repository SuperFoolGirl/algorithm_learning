// 1 自己写的 30分 原因在于递归里面 ans和cnt用的太危险 重复计数了
// 重点学习一下2解里面 是如何规避ans和cnt带来的问题的
// 经过1683的熏陶，可以初步判定这道题也不需要回溯
#include <iostream>
using namespace std;
#define maxn 110

int m, n;
int ans = 0;
char map[maxn][maxn] = {'\0'};
int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};
bool vis[maxn][maxn] = {false};

// 简单说一下自己的思路
// 联通问题 我认为：在联通区域内的每个点，自己都要至少有一个联通的对象
// 由于vis数组的存在，如果b联通到a，那么a是无法搜索到b的
// 对于中心是水坑的点，除去已经搜索过的点，如果周围八个再没有其他联通水坑，那就结束了
void dfs(int x, int y)
{
    vis[x][y] = true;
    int cnt = 0;
    for (int i = 0; i < 8; i++)
    {
        int nextX = x + dx[i];
        int nextY = y + dy[i];
        if (nextX < 1 || nextX > n || nextY < 1 || nextY > m)
            continue;
        if (vis[nextX][nextY] == true)
            continue;
        // 基于上方注释的思路描述 我们只需要沿着水坑去找下一个水坑即可，如果找不到那联通就断了。不需要去走非水坑。
        if (map[nextX][nextY] == 'W')
        {
            dfs(nextX, nextY);
            cnt++;
        }
    }
    if (map[x][y] == 'W' && cnt == 0)
        ans++;
}

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
            cin >> map[i][j];
    }

    // 这里进入地图的方式 第一次运用
    // 以往都是一个dfs直接跑完全图 本题中不适用
    // 这里是遍历地图 结合vis数组选择合适的点进入进行dfs 
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (vis[i][j] == false && map[i][j] == 'W')
                dfs(i, j);
        }
    }
    cout << ans;
    return 0;
}



// 2 ai改进版 全过
#include <iostream>
using namespace std;

#define maxn 110

int m, n;
int ans = 0;
char map[maxn][maxn] = {'\0'};
int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1}; // 八个方向的偏移量
int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};
bool vis[maxn][maxn] = {false};

void dfs(int x, int y)
{
    // 标记当前点为已访问
    vis[x][y] = true;

    // 向八个方向扩展
    for (int i = 0; i < 8; i++)
    {
        int nextX = x + dx[i];
        int nextY = y + dy[i];

        // 检查边界条件
        if (nextX < 1 || nextX > n || nextY < 1 || nextY > m)
            continue; // 越界，跳过

        // 检查是否为水坑且未访问过
        if (map[nextX][nextY] == 'W' && !vis[nextX][nextY])
            dfs(nextX, nextY); // 递归搜索
    }
}

int main()
{
    cin >> n >> m;

    // 读入地图
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> map[i][j];

    // 遍历整个地图
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            // 如果当前点是水坑且未访问过，开始 DFS
            if (map[i][j] == 'W' && !vis[i][j])
            {
                // 直接一开始就增加 是我曾想过的思路
                ans++;     // 增加水坑计数
                // 执行下面的dfs后，一定能走完一整个水坑，且水坑里面每个元素都标记了true 不会再走到了
                // 这样就规避了ans和cnt带来的问题
                dfs(i, j); // 标记所有连通的水坑
            }
        }
    }

    // 输出结果
    cout << ans << endl;

    return 0;
}