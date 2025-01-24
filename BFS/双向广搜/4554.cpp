#include <iostream>
#include <deque>
#include <cstring>
#define MAXN 510
using namespace std;

int n, m;
char board[MAXN][MAXN];
int dist[MAXN][MAXN];
deque<pair<int, int>> q;
int x1, x2, y11, y2;
int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};

int bfs(int x, int y)
{
    q.push_back({x, y});
    dist[x][y] = 0;

    while (!q.empty())
    {
        auto t = q.front();
        q.pop_front();
        char ch = board[t.first][t.second];

        for (int i = 0; i < 4; i++)
        {
            int a = t.first + dx[i];
            int b = t.second + dy[i];

            if (a < 0 || a > n - 1 || b < 0 || b > m -1)
                continue;
            if (dist[a][b] != -1)
                continue;
            
            // 0边权
            if (board[a][b] == ch)
            {
                // dist不再记录步数，而是消费
                // 从这里就可以看出来边权的区别
                dist[a][b] = dist[t.first][t.second];

                // 0边权的情况下，直接插入队列头部
                q.push_front({a, b});
            }

            // 1边权
            if (board[a][b] != ch)
            {
                dist[a][b] = dist[t.first][t.second] + 1;

                // 1边权的情况下，直接插入队列尾部
                q.push_back({a, b});
            }

            if (a == x2 && b == y2)
                return dist[a][b];
        }
    }
    return -1; // 没必要写，但看警告太难受
}

int main()
{
    while (cin >> n >> m, n || m) // 如果n和m都为0，则结束循环
    {
        for (int i = 0; i < n; i++)
            cin >> board[i]; // 直接用列指针的方式读入字符串
        cin >> x1 >> y11 >> x2 >> y2;
        memset(dist, -1, sizeof dist);
        q.clear(); // 双端队列有clear()方法
        cout << bfs(x1, y11) << endl;
    }
    return 0;
}