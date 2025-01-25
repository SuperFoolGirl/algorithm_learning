// 介绍下哈希表的用法，没有用到双向bfs
#include <iostream>
#include <queue>
#include <unordered_map>
#include <string>
using namespace std;

string end1 = "123804765";
unordered_map<string, int> dist;
queue<string> q;
int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};

int bfs(string start)
{
    q.push(start);
    dist[start] = 0;

    while (!q.empty())
    {
        auto t = q.front();
        q.pop();

        // return写在这还真有讲究
        // 不要把return写在for循环里，可能导致 队列中存在更优路径时提前返回非最优解
        // 当模板背过
        // 对每一个队首进行判断，是合乎逻辑的。同时出口位置也和dfs类似
        // 注意上面说了 可能出问题。以前我没注意这个问题但也过了，只能说侥幸
        if (t == end1)
            return dist[t];

        int distance = dist[t]; // 一定要先取出来，因为后面的操作会改变t

        // 将一维坐标转换为二维坐标，掌握这个除模
        int position_zero = t.find('0'); // 需要调用函数的值就另开一个变量储存，别每次都调函数
        int x = position_zero / 3;       // string的方法
        int y = position_zero % 3;

        for (int i = 0; i < 4; i++)
        {
            int a = x + dx[i];
            int b = y + dy[i];

            if (a < 0 || a >= 3 || b < 0 || b >= 3)
                continue;

            int tmp = a * 3 + b;            // 二维坐标转换为一维坐标
            swap(t[position_zero], t[tmp]); // 交换操作总是以0为对象进行，这是题干要求

            if (!dist.count(t)) // count()为哈希表方法。由于该STL不允许重复元素，因此用于检查元素是否存在，参数为键
            {
                dist[t] = distance + 1;
                q.push(t);
            }

            // 看上面，如果我们遇到了能加入队列的情况，那么在swap的情况下已经push了；这里恢复现场不影响push操作
            swap(t[position_zero], t[tmp]); // 恢复现场，因为是for循环
        }
    }
    return -1;
}

int main()
{
    string start;
    cin >> start;
    cout << bfs(start) << endl;
    return 0;
}




// 双向bfs
#include <iostream>
#include <queue>
#include <unordered_map>
using namespace std;

string end1 = "123804765";
unordered_map<string, int> dist;
queue<string> q;
unordered_map<string, int> vis;
int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};

int bfs(string start)
{
    // 双向bfs的模板是要特判起点终点相同的！
    if (start == end1)
        return 0;

    q.push(start);
    q.push(end1);
    dist[start] = 0;
    dist[end1] = 0;
    vis[start] = 1;
    vis[end1] = 2;

    while (!q.empty())
    {
        auto t = q.front();
        q.pop();

        int distance = dist[t];
        int mark = vis[t];
        int position_zero = t.find('0');
        int x = position_zero / 3;
        int y = position_zero % 3;

        for (int i = 0; i < 4; i++)
        {
            int a = x + dx[i];
            int b = y + dy[i];

            if (a < 0 || a >= 3 || b < 0 || b >= 3)
                continue;

            int tmp = a * 3 + b;
            swap(t[position_zero], t[tmp]);

            if (vis[t] + mark == 3) // vis[t]是对面标记的，mark是队首标记的
                return dist[t] + distance + 1;

            if (!dist.count(t)) // 检查重复访问
            {
                dist[t] = distance + 1;
                q.push(t);
                vis[t] = vis[t] == 0 ? mark : vis[t];
            }

            swap(t[position_zero], t[tmp]);
        }
    }
    return -1;
}

int main()
{
    string start;
    cin >> start;
    cout << bfs(start) << endl;
    return 0;
}