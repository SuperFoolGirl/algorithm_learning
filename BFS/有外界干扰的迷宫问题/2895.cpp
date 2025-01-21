// 自己写的 尽力了 只有一个点没过
// 理所应当地写得很丑陋...

// 简单说一下思路
// 首先把零时刻炸的都标记为true
// 找出下一时刻被炸的所有区域，vis标为true以禁止访问。需要配合sort排序
// 如果它是下一步的目标之一，那这个位置就走不了
// 另一方面 被炸的地方永远都走不了 符合vis数组的行为
// 考虑到bfs是同时推进一步的搜索方法，也不需要回溯。被炸的地方只与时刻有关，同时推进一步意味着处于同一时刻
// 感觉这个思路更加简单

// 如何判断到达安全地点？
// 我初步的想法是，如果所有流星都炸完了，那么就是安全的
// 但是这个思路有问题，因为有可能有些流星炸不到，但是也是安全的
// 比如说，起点就是安全的，所有流星炸完了都没影响到起点
// 所以 另开一个所有流星炸完后的地图
// 到达一个点后，如果另一张地图显示这个点永远没炸到，那就到了目标地点了
// 因此，不用再考虑流星炸多少的问题

#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;
#define maxn 310

int m;
int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};
int map[maxn][maxn] = {0};
queue<pair<int, int>> q;

// 大多数情况下，vis和dist没必要同时存在。dist==-1就是vis==false
// 但是本题属于特殊情况，就是流星炸到的地方，不是一次性的，而是有时刻的
// 不用vis数组会导致本来AC的代码不AC，具体bug不细究了
bool vis[maxn][maxn] = {false};
int dist[maxn][maxn] = {0};

bool boomedMap[maxn][maxn] = {false};

// 储存流星信息
struct Shot
{
    int x;
    int y;
    int time;
} shot[50010];

int bfs(int x, int y)
{
    // 预处理
    // ----------------------------------------------------------------------------
    dist[x][y] = 0;
    vis[x][y] = true;
    q.push({x, y});
    int idx = -1;

    // 处理零时刻的爆炸
    for (int i = idx + 1; shot[i].time == 0; i++)
    {
        idx = i;
        vis[shot[i].x][shot[i].y] = true;
        for (int j = 0; j < 4; j++)
        {
            int aroundX = shot[i].x + dx[j];
            int aroundY = shot[i].y + dy[j];

            if (aroundX < 0 || aroundX > 300 || aroundY < 0 || aroundY > 300)
                continue;
            vis[aroundX][aroundY] = true;
        }
    }
    // ----------------------------------------------------------------------------


    // bfs
    while (!q.empty())
    {
        auto head = q.front();
        q.pop();

        // 找出下一时刻所有爆炸点
        for (int i = idx + 1; shot[i].time == dist[head.first][head.second] + 1; i++) // 注意下一时刻的表述
        {
            idx = i; // 这个更新蛮巧妙的
            // 已经走过的地方已经标为true了，相当于已经炸了，重复处理也无妨
            vis[shot[i].x][shot[i].y] = true;
            for (int j = 0; j < 4; j++)
            {
                int aroundX = shot[i].x + dx[j];
                int aroundY = shot[i].y + dy[j];

                if (aroundX < 0 || aroundX > 300 || aroundY < 0 || aroundY > 300)
                    continue;

                vis[aroundX][aroundY] = true;
            }
        }

        // 开始跑图
        for (int i = 0; i < 4; i++)
        {
            int nextX = head.first + dx[i];
            int nextY = head.second + dy[i];

            if (nextX < 0 || nextX > 300 || nextY < 0 || nextY > 300)
                continue;
            if (vis[nextX][nextY] == true)
                continue;

            vis[nextX][nextY] = true;
            q.push({nextX, nextY});
            dist[nextX][nextY] = dist[head.first][head.second] + 1;

            // 如果到达了一个安全地点，那么直接返回
            if (boomedMap[nextX][nextY] == false)
                return dist[nextX][nextY];
        }
    }

    // 队列空了，无路可走，没有找到安全地点
    return -1;
}

int main()
{
    cin >> m;
    for (int i = 0; i < m; i++)
        cin >> shot[i].x >> shot[i].y >> shot[i].time;
    memset(dist, -1, sizeof dist);

    // 结构体数组按time排序，以节约bfs中遍历时间
    sort(shot, shot + m, [](Shot a, Shot b) { return a.time < b.time; }); // lambda表达式 匿名函数

    // 处理爆炸后的地图
    for (int i = 0; i < m; i++)
    {
        boomedMap[shot[i].x][shot[i].y] = true;
        for (int j = 0; j < 4; j++)
        {
            int aroundX = shot[i].x + dx[j];
            int aroundY = shot[i].y + dy[j];
            if (aroundX < 0 || aroundX > 300 || aroundY < 0 || aroundY > 300)
                continue;
            boomedMap[aroundX][aroundY] = true;
        }
    }

    cout << bfs(0, 0);
    return 0;
}