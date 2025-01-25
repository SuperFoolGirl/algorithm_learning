#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

const int MAXN = 105;
const int INF = 0x3f3f3f3f;

int m, n;
int color[MAXN][MAXN];
int dist[MAXN][MAXN][2][2]; // x, y, magic, temp_color

// 数组意识到开成四维，那pair也肯定用不了了 上结构体
struct Node
{
    int x, y;
    int magic; // 0: 未使用魔法，1: 使用魔法
    int temp_color; // 神之一手，记录当前状态的颜色
    int cost;

    Node(int x, int y, int magic, int temp_color, int cost)
        : x(x), y(y), magic(magic), temp_color(temp_color), cost(cost) {}

    // 重载比较运算符，用于优先队列的自动排序
    bool operator>(const Node &other) const { return cost > other.cost; }
};

int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};


// 状态转移：
// 未使用魔法时：正常移动或使用魔法。若目标格子有色，计算颜色差异的花费；若目标格子无色，使用魔法并记录临时颜色。
// 处于魔法状态时：必须移动到有色格子，计算颜色差异的花费，并恢复可施法状态。

// 这个题是如何处理魔法状态的？
// 就是运用多维数组
// 当使用魔法时，dist参数3直接改成1
// 这种大胆开多维数组的思想值得学习

// 另外就是颜色恢复
// 做法是使用结构体储存临时更换的颜色，而color是锁死的

// 一个点是否使用魔法，是作为一个队列成员来考虑的
// 并非是通过数组、结构体等记录
// 如果这个点使用了魔法，那我直接把这个状态push进去
// 如果再次走到这个点，使用魔法与否完全看push它时候的情况
// 而千万不能考虑用结构体或者数组全局地对这个点进行魔法使用标记

// 这里我说得可能没那么清楚
// 总之 属性一律放在结构体中，通过多维数组来映射
// 属性为什么放在结构体？因为队列的元素是结构体，把属性放在结构体里，才能入队，才能实现这些属性在不同轮次的访问中的变化
int dijkstra()
{
    priority_queue<Node, vector<Node>, greater<Node>> pq; // 最小堆
    memset(dist, 0x3f, sizeof(dist));

    int start_color = color[1][1];
    dist[1][1][0][start_color] = 0; // 解读四个属性：点(1,1)处于未使用魔法状态，且颜色为start_color，花费为0
    // 自动排序，按花费从小到大排序
    pq.push(Node(1, 1, 0, start_color, 0)); // 构造函数写法。当然也可以直接写pq.push({1, 1, 0, start_color, 0});

    while (!pq.empty())
    {
        Node node = pq.top();
        pq.pop();

        int x = node.x, y = node.y;
        int magic = node.magic, temp_color = node.temp_color;
        int cost = node.cost;

        if (x == m && y == m)
            return cost; // 到达终点。优先队列的性质保证了最小路径总权值，具体原理下文有解释，但这里可以简单说明：同普通bfs一样，最先到的就是最优解


        if (cost > dist[x][y][magic][temp_color]) // 剪枝不好的情况，注意位置，写在拓展前面
            continue;

        for (int i = 0; i < 4; ++i)
        {
            int a = x + dx[i], b = y + dy[i];
            if (a < 1 || a > m || b < 1 || b > m)
                continue;

            if (magic == 0)
            { 
                // 当前未使用魔法
                int current_color = color[x][y];
                if (color[a][b] != -1)
                { 
                    // 目标格子有色
                    int next_color = color[a][b];
                    int new_cost = cost + (current_color != next_color); // 有趣的写法

                    // 统一讲一下 这里为什么要再加一次判定
                    // 普通bfs的vis判定是在扩展里面写的
                    // 在优先队列里，我们写到了外面，这样就带来一个问题
                    // 还是后来居上的问题
                    // 当前(a,b)这个点，不一定是只能通过node及其附属状态才能达到的
                    // 我们只能挡住node及其附属状态，保证其不会第二次访问，
                    // 因此有被多次访问的可能
                    // 那么就会多出来很多可以被剪枝的情况了
                    // 这里的判定就是在剪枝
                    if (new_cost < dist[a][b][0][next_color])
                    {
                        dist[a][b][0][next_color] = new_cost;
                        pq.push(Node(a, b, 0, next_color, new_cost)); // 注意参数四是node.temp_color，和color数组进行区分。color数组记录输入的地图，而temp_color记录当前状态。
                    }
                }
                else
                { 
                    // 目标格子无色，使用魔法
                    int new_cost = cost + 2;
                    if (new_cost < dist[a][b][1][current_color]) // 直接把node点的color塞给无色点。也就是说，无色点的color是node点的color，不需要考虑另一种颜色。这是贪心。
                    {
                        dist[a][b][1][current_color] = new_cost;
                        pq.push(Node(a, b, 1, current_color, new_cost)); // 比较参数四的区别。如果使用了魔法，那么(a,b)的temp_color就是node点的color；反之则不变
                    }
                }
            }
            else
            { 
                // 当前处于魔法后的状态。a,b是扩展出去的点，本来node点就是魔法点，所以扩展出去的a,b必须是有色格子
                if (color[a][b] == -1)
                    continue; // 必须移动到有色格子

                int next_color = color[a][b];
                int new_cost = cost + (temp_color != next_color);
                if (new_cost < dist[a][b][0][next_color]) // (a,b)是有色格子，dist参数三必然是0
                {
                    dist[a][b][0][next_color] = new_cost;
                    pq.push(Node(a, b, 0, next_color, new_cost));
                }
            }
        }
    }
    return -1;
}

int main()
{
    cin >> m >> n;
    memset(color, -1, sizeof(color));
    for (int i = 0; i < n; ++i)
    {
        int x, y, c;
        cin >> x >> y >> c;
        color[x][y] = c;
    }
    cout << dijkstra() << endl;
    return 0;
}

// 下面我自己又自己写了一遍
// 好好体会一下剪枝的部分
#include <iostream>
#include <queue>
#include <cstring>
using namespace std;
#define MAXN 105

struct node
{
    int x, y;
    bool magic;
    int status_color;
    int cost; // 由dist映射

    bool operator>(const Node &rhs) const { return cost > rhs.cost; } // 写小于会报错？？
};
int m, n;
int dist[MAXN][MAXN][2][2];
int color[MAXN][MAXN];
priority_queue<node, vector<node>, greater<node>> q;
int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};

int dijkstra()
{
    memset(dist, 0x3f, sizeof dist); // 这里必须初始化为无穷大，因为我们要将dist更新为最小值
    dist[1][1][0][color[1][1]] = 0;
    q.push({1, 1, false, color[1][1], 0});

    while (!q.empty())
    {
        auto t = q.top(); // 没有front();
        q.pop();

        // ---------------------------------------------------------------------------------
        // !!!重点!!!
        // 原本这个重复访问的判定是写在扩展点里面的
        // 但是拓展点的magic和status_color是未知的
        // 我们能拿到的具体信息，就是目前的队首
        // 但不能写!=0x3f3f3f3f,因为起点的dist已经更新为0了，那样写的话起点无法进入扩展

        // 由于优先队列的特性，保证第一次访问这个点的边权和一定最小(这里说的点，指的是满足dist的四个参数。是否使用魔法以及使用魔法后当前的颜色也是这个点的参数，不能只看坐标)
        // 但是如果不加这个判定，后来居上的点可能会把这个点的边权更新为更小的值
        // 但是这个点的边权已经是最小的了，所以不需要再次更新。所以起到vis的作用
        if (t.cost > dist[t.x][t.y][t.magic][t.status_color])
            continue;
        // ---------------------------------------------------------------------------------

        // 把终点判定拿出扩展的作用之前一直没想到
        // 是为了防止起点与终点重合！
        // 只要到了终点，不管魔法判定和颜色，直接返回
        if (t.x == m && t.y == m)
            return t.cost;

        // 第一个点必然有颜色，直接往外扩
        for (int i = 0; i < 4; i++)
        {
            int a = t.x + dx[i];
            int b = t.y + dy[i];

            // 扩展判定其实都可以拿到外面去
            if (a < 1 || a > m || b < 1 || b > m)
                continue;

            // 当前队列成员是否使用了魔法
            if (t.magic == false)
            {
                if (color[a][b] != -1)
                {
                    int new_cost = color[a][b] == t.status_color ? t.cost : t.cost + 1;
                    // 点(a,b)可能重复访问，不一定仅仅是通过t扩展来，所以外面仅仅拦住t是不够的
                    // 另外提一个思想：不确定这个判定有没有用，那就写上去，反正不会错
                    if (new_cost < dist[a][b][0][color[a][b]])
                    {
                        dist[a][b][0][color[a][b]] = new_cost;
                        q.push({a, b, false, color[a][b], new_cost});
                    }
                }
                else
                {
                    int new_cost = t.cost + 2;
                    if (new_cost < dist[a][b][1][t.status_color])
                    {
                        dist[a][b][1][t.status_color] = new_cost; // 把使用魔法的情况记下来，对应颜色是使用魔法后的颜色
                        q.push({a, b, true, t.status_color, new_cost});
                    }
                }
            }
            else
            {
                if (color[a][b] == -1)
                    continue;

                int new_cost = color[a][b] == t.status_color ? t.cost : t.cost + 1;
                if (new_cost < dist[a][b][0][color[a][b]])
                {
                    dist[a][b][0][color[a][b]] = new_cost; // 记录下一步
                    q.push({a, b, false, color[a][b], new_cost});
                }
            }
        }
    }
    return -1;
}

int main()
{
    cin >> m >> n;
    memset(color, -1, sizeof color);
    for (int i = 1; i <= n; i++)
    {
        int x, y, c;
        cin >> x >> y >> c;
        color[x][y] = c;
    }
    cout << dijkstra() << endl;
    return 0;
}