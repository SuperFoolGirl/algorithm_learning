// 自己写的 尽力了
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

            if (aroundX < 0 || aroundX > 301 || aroundY < 0 || aroundY > 301) // 这地方让卡了！焦土会再扩一圈！但0那个点无妨，改成-1的话直接数组越界了
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

                if (aroundX < 0 || aroundX > 301 || aroundY < 0 || aroundY > 301)
                    continue;

                vis[aroundX][aroundY] = true;
            }
        }

        // 开始跑图
        for (int i = 0; i < 4; i++)
        {
            int nextX = head.first + dx[i];
            int nextY = head.second + dy[i];

            if (nextX < 0 || nextY < 0) // 注意人的范围
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
            if (aroundX < 0 || aroundX > 301 || aroundY < 0 || aroundY > 301)
                continue;
            boomedMap[aroundX][aroundY] = true;
        }
    }

    cout << bfs(0, 0);
    return 0;
}




// 视频解法：并不是只开一张爆炸地图，而是储存爆炸时间
// 考虑一个问题：同一个点可能被多次炸，要记录最早时间
// 这样连结构体都不需要了，我那段代码最恶心的点就是结构体及其排序，还引入一个idx，可读性非常差
// 然后看当前时刻是否符合下一步安全地点
// 体会一下自己的思维缺陷

#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
#define maxn 310
using namespace std;

int m;
// 拓展方向数组 加上原点。遍历时炸弹取5，人取4
int dx[] = {-1, 0, 1, 0, 0};
int dy[] = {0, 1, 0, -1, 0};
int boomed[maxn][maxn];
int dist[maxn][maxn];
queue<pair<int, int>> q;

int bfs(int x, int y)
{
    q.push({x, y});
    dist[x][y] = 0;

    while (!q.empty())
    {
        auto head = q.front();
        q.pop();

        for (int i = 0; i < 4; i++) // 人取4
        {
            int nextX = head.first + dx[i];
            int nextY = head.second + dy[i];

            if (nextX < 0 || nextY < 0)
                continue;
            if (dist[nextX][nextY] != -1)
                continue;
            if (dist[head.first][head.second] + 1 >= boomed[nextX][nextY]) // 注意这个判断条件
                continue;

            q.push({nextX, nextY});
            dist[nextX][nextY] = dist[head.first][head.second] + 1;

            // 判断是否到达安全地点
            if (boomed[nextX][nextY] == 0x3f3f3f3f) // 如果走到没被炸的地方
                return dist[nextX][nextY];
        }
    }
    return -1;
}

int main()
{
    cin >> m;
    // 体会下memset的作用。统一初始化为-1/0/0x3f，下面对数组赋值。如果遍历到-1/0/0x3f，就意味着这个点没被赋值过
    memset(dist, -1, sizeof dist);
    // 使用 memset 初始化时，0x3f 会将每个字节设置为 0x3f，因此 int 类型的变量会被初始化为 0x3f3f3f3f
    memset(boomed, 0x3f, sizeof boomed); // 这里初始化为无穷大 是为了配合下方min赋值
    for (int i = 0; i < m; i++)
    {
        int x, y, t;
        cin >> x >> y >> t;
        for (int j = 0; j < 5; j++) // 炸弹取5
        {
            int aroundX = x + dx[j];
            int aroundY = y + dy[j];
            if (aroundX < 0 || aroundX > 301 || aroundY < 0 || aroundY > 301)
                continue;
            boomed[aroundX][aroundY] = min(boomed[aroundX][aroundY], t);
        }
    }
    cout << bfs(0, 0);
    return 0;
}