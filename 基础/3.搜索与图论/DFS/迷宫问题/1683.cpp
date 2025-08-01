#include <iostream>
using namespace std;
#define maxn 30

int w, h;
char map[maxn][maxn] = {0};
int ans = 1;
bool vis[maxn][maxn] = {0};
int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};

void dfs(int x, int y)
{
    for (int i = 0; i < 4; i++)
    {
        int nextX = x + dx[i], nextY = y + dy[i];

        // 这里三层continue 先不纠结压成一行能不能解决 至少写成三个是很容易理解，并且可以确定这个逻辑没有问题
        // 满足不越界，才能进而满足是否vis了等等...
        // 重点掌握下continue的运用吧 平时用的真不算多
        if (nextX < 1 || nextX > h || nextY < 1 || nextY > w)
            continue;
        if (map[nextX][nextY] != '.')
            continue;
        if (vis[nextX][nextY] == true)
            continue;

        vis[nextX][nextY] = true;
        ans++;
        dfs(nextX, nextY);
        // 不需要回溯：
        // 回溯的作用是撤销访问标记，以便尝试其他路径。
        // 在本代码中不需要回溯，因为题目要求的是统计所有可达的瓷砖数量，而不是寻找某条路径。
        // 回溯通常用于路径搜索问题，当需要尝试多条路径时，撤销访问标记以便重新探索。
    }
}

int main()
{
    pair<int, int> start;
    cin >> w >> h;
    for (int i = 1; i <= h; i++)
    {
        for (int j = 1; j <= w; j++)
        {
            cin >> map[i][j];
            if (map[i][j] == '@')
            {
                start.first = i;
                start.second = j;
            }
        }
    }
    vis[start.first][start.second] = true;
    dfs(start.first, start.second);
    cout << ans;
    return 0;
}